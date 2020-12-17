#include <stdafx.hpp>

#include <Hooks/CBaseInitializationState.hpp>
#include <Hooks/CInitializationState.hpp>
#include <Hooks/CRunningState.hpp>
#include <Hooks/CShutdownState.hpp>
#include <Hooks/Main.hpp>

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    using namespace RED4ext::Hooks;
    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        Main::Attach(aModule);
        CBaseInitializationState::Attach();
        CInitializationState::Attach();
        CRunningState::Attach();
        CShutdownState::Attach();

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        Main::Detach();
        CShutdownState::Detach();
        CRunningState::Detach();
        CInitializationState::Detach();
        CBaseInitializationState::Detach();

        break;
    }
    }

    return TRUE;
}
