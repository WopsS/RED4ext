#include "Proxies/winmm.hpp"

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    (void)aReserved;

    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        try
        {
            if (!winmm::LoadOriginal())
            {
                return FALSE;
            }

            constexpr auto msgCaption = L"RED4ext";
            constexpr auto dir = L"red4ext";
            constexpr auto dll = L"RED4ext.dll";

            std::wstring fileName;
            auto hr = wil::GetModuleFileNameW(nullptr, fileName);
            if (FAILED(hr))
            {
                wil::unique_hlocal_ptr<wchar_t> buffer;
                auto errorCode = GetLastError();

                FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                                  FORMAT_MESSAGE_IGNORE_INSERTS,
                              nullptr, errorCode, LANG_USER_DEFAULT, wil::out_param_ptr<LPWSTR>(buffer), 0, nullptr);

                auto caption = fmt::format(L"{} (error {})", msgCaption, errorCode);
                auto message = fmt::format(L"{}\nCould not get the file name.", buffer.get());
                MessageBox(nullptr, message.c_str(), caption.c_str(), MB_ICONERROR | MB_OK);

                return TRUE;
            }

            std::error_code fsErr;
            std::filesystem::path exePath = fileName;
            auto rootPath = exePath
                                .parent_path()  // Resolve to "x64" directory.
                                .parent_path()  // Resolve to "bin" directory.
                                .parent_path(); // Resolve to game root directory.

            auto modPath = rootPath / dir;
            if (std::filesystem::exists(modPath, fsErr))
            {
                auto dllPath = modPath / dll;
                if (!LoadLibrary(dllPath.c_str()))
                {
                    wil::unique_hlocal_ptr<wchar_t> buffer;
                    auto errorCode = GetLastError();

                    FormatMessage(
                        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                        nullptr, errorCode, LANG_USER_DEFAULT, wil::out_param_ptr<LPWSTR>(buffer), 0, nullptr);

                    auto caption = fmt::format(L"{} (error {})", msgCaption, errorCode);
                    auto message =
                        fmt::format(L"{}\n{}\n\nRED4ext could not be loaded.", buffer.get(), dllPath.c_str());
                    MessageBox(nullptr, message.c_str(), caption.c_str(), MB_ICONERROR | MB_OK);
                }
            }
            else if (fsErr)
            {
                auto message =
                    fmt::format(L"RED4ext could not be loaded because of a filesystem error ({}).", fsErr.value());
                MessageBox(nullptr, message.c_str(), msgCaption, MB_ICONERROR | MB_OK);
            }
        }
        catch (const std::exception& e)
        {
            auto message = fmt::format("An exception occured in RED4ext's loader.\n\n{}", e.what());
            MessageBoxA(nullptr, message.c_str(), "RED4ext", MB_ICONERROR | MB_OK);
        }
        catch (...)
        {
            MessageBox(nullptr, L"An unknown exception occured in RED4ext's loader.", L"RED4ext", MB_ICONERROR | MB_OK);
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
