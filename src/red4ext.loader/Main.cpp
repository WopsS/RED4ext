#include "stdafx.hpp"
#include "VersionDll.hpp"

HANDLE s_mutex = nullptr;

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        if (!LoadOriginalDll())
        {
            return FALSE;
        }
   
        constexpr auto name = L"RED4ext";
        s_mutex = CreateMutex(nullptr, true, name);

        // Only load "RED4ext" in game's process. The game process is started first and then the crash handler is
        // created.
        auto err = GetLastError();
        if (err == ERROR_ALREADY_EXISTS)
        {
            return TRUE;
        }
        else if (err != ERROR_SUCCESS)
        {
            wchar_t* buffer = nullptr;
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                          nullptr, err, LANG_USER_DEFAULT, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);

            auto message = fmt::format(L"{}\n\nRED4ext could not be loaded, error code 0x{:X}.", buffer, err);
            MessageBox(nullptr, message.c_str(), name, MB_ICONERROR | MB_OK);

            LocalFree(buffer);
            buffer = nullptr;
            return FALSE;
        }

        constexpr auto pathLength = MAX_PATH + 1;
        constexpr auto modDir = L"red4ext";
        constexpr auto modDll = L"RED4ext.dll";

        // Try to get the executable path until we can fit the length of the path.
        std::wstring filename;
        do
        {
            filename.resize(filename.size() + pathLength, '\0');

            auto length = GetModuleFileName(nullptr, filename.data(), static_cast<uint32_t>(filename.size()));
            if (length > 0)
            {
                // Resize it to the real, std::filesystem::path" will use the string's length instead of recounting it.
                filename.resize(length);
            }
        } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);

        std::filesystem::path exePath(filename);
        auto rootPath = exePath
                            .parent_path()  // Resolve to "x64" directory.
                            .parent_path()  // Resolve to "bin" directory.
                            .parent_path(); // Resolve to game root directory.

        auto modPath = rootPath / modDir;
        if (!std::filesystem::exists(modPath))
        {
            auto message = fmt::format(L"The directory '{}' does not exist, RED4ext will not be loaded.\r\n\r\n"
                                       L"If this is intended please remove 'version.dll' from '{}' directory.",
                                       modPath.c_str(), exePath.remove_filename().c_str());

            MessageBox(nullptr, message.c_str(), name, MB_ICONWARNING | MB_OK);
        }

        auto dllPath = modPath / modDll;
        if (!LoadLibrary(dllPath.c_str()))
        {
            wchar_t* buffer = nullptr;
            auto errorCode = GetLastError();

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                          nullptr, errorCode, LANG_USER_DEFAULT, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);

            auto message = fmt::format(L"{}\n\nRED4ext could not be loaded, error code 0x{:X}.", buffer, errorCode);
            MessageBox(nullptr, message.c_str(), name, MB_ICONERROR | MB_OK);

            LocalFree(buffer);
            buffer = nullptr;
        }

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        if (s_mutex)
        {
            ReleaseMutex(s_mutex);
            CloseHandle(s_mutex);
        }

        break;
    }
    }

    return TRUE;
}
