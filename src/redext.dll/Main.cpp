#include <stdafx.hpp>
#include <Hooks/Main.hpp>

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    using namespace REDext::Hooks;
    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);
        Main::Attach(aModule);

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        Main::Detach();
        break;
    }
    }

    return TRUE;
}
