#include "stdafx.hpp"
#include "App.hpp"
#include "Utils.hpp"
#include "Image.hpp"

static HANDLE g_instanceMutex = nullptr;

BOOL APIENTRY DllMain(HMODULE aModule, DWORD aReason, LPVOID aReserved)
{
    const auto image = Image::Get();

    switch (aReason)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(aModule);

        if (!image->IsCyberpunk())
        {
            break;
        }

        App::Construct();

        break;
    }
    case DLL_PROCESS_DETACH:
    {
        if (!image->IsCyberpunk())
        {
            break;
        }

        App::Destruct();

        if (g_instanceMutex)
        {
            ReleaseMutex(g_instanceMutex);
            CloseHandle(g_instanceMutex);
        }

        break;
    }
    }

    return TRUE;
}
