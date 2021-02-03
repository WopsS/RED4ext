#include "stdafx.hpp"

#include "Hooks/CInitializationState.hpp"
#include "Hooks/CShutdownState.hpp"
#include "Hooks/Main.hpp"

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        Main::Attach(aModule);
        CInitializationState::Attach();
        CShutdownState::Attach();

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        CShutdownState::Detach();
        CInitializationState::Detach();
        Main::Detach();

        break;
    }
    }

    return TRUE;
}
