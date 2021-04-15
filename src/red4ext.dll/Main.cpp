#include "stdafx.hpp"

#include "App.hpp"
#include "Hooks/CInitializationState.hpp"
#include "Hooks/CShutdownState.hpp"
#include "Hooks/Main.hpp"

HANDLE s_mutex = nullptr;

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        constexpr auto name = L"RED4ext";
        s_mutex = CreateMutex(nullptr, true, name);

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

            auto message = fmt::format(L"{}\n\n{} could not be loaded, error code 0x{:X}.", buffer, name, err);
            MessageBox(nullptr, message.c_str(), name, MB_ICONERROR | MB_OK);

            LocalFree(buffer);
            buffer = nullptr;

            // Just to be safe.
            if (s_mutex)
            {
                ReleaseMutex(s_mutex);
                CloseHandle(s_mutex);
            }

            return FALSE;
        }

        App::Construct(aModule);

        Main::Attach();
        CInitializationState::Attach();
        CShutdownState::Attach();

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        CShutdownState::Detach();
        CInitializationState::Detach();
        Main::Detach();

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
