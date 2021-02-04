#include "stdafx.hpp"
#include "VersionDll.hpp"

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

        constexpr auto EXE = L"Cyberpunk2077.exe";
        constexpr auto PATH_LENGTH = MAX_PATH + 1;
        constexpr auto MOD_DIR = L"red4ext";
        constexpr auto MOD_DLL = L"RED4ext.dll";

        // Try to get the executable path until we can fit the length of the path.
        std::wstring filename;
        do
        {
            filename.resize(filename.size() + PATH_LENGTH, '\0');

            auto length = GetModuleFileName(nullptr, filename.data(), static_cast<uint32_t>(filename.size()));
            if (length > 0)
            {
                // Resize it to the real, std::filesystem::path" will use the string's length instead of recounting it.
                filename.resize(length);
            }
        } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);

        // Only load "RED4ext" in game's process.
        std::filesystem::path exePath(filename);
        if (exePath.filename() != EXE)
        {
            return TRUE;
        }

        auto rootPath = exePath
                            .parent_path()  // Resolve to "x64" directory.
                            .parent_path()  // Resolve to "bin" directory.
                            .parent_path(); // Resolve to game root directory.

        auto modPath = rootPath / MOD_DIR;
        if (!std::filesystem::exists(modPath))
        {
            auto message = fmt::format(L"The directory '{}' does not exist, RED4ext will not be loaded.\r\n\r\n"
                                       L"If this is intended please remove 'version.dll' from '{}' directory.",
                                       modPath.c_str(), exePath.remove_filename().c_str());

            MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONWARNING | MB_OK);
        }

        auto dllPath = modPath / MOD_DLL;
        if (!LoadLibrary(dllPath.c_str()))
        {
            wchar_t* buffer = nullptr;
            auto errorCode = GetLastError();

            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                          nullptr, errorCode, LANG_USER_DEFAULT, reinterpret_cast<LPWSTR>(&buffer), 0, nullptr);

            auto message = fmt::format(L"{}\n\nRED4ext could not be loaded, error code 0x{:X}.", buffer, errorCode);
            MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONERROR | MB_OK);

            LocalFree(buffer);
            buffer = nullptr;
        }

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        break;
    }
    }

    return TRUE;
}
