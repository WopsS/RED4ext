#include "stdafx.hpp"
#include "Hooks/CShutdownState.hpp"
#include "App.hpp"
#include "REDhook.hpp"

#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameStates.hpp>

namespace
{
bool _CShutdownState_Run(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp);
REDhook<decltype(&_CShutdownState_Run)> CShutdownState_Run;

bool _CShutdownState_Run(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
   /* auto pluginsManager = app->GetPluginsManager();

    pluginsManager->UnloadAll();*/
    return CShutdownState_Run(aThis, aApp);
}
} // namespace

void CShutdownState::Attach()
{
    new (&CShutdownState_Run) REDhook<decltype(&_CShutdownState_Run)>(
        {0x48, 0x89, 0x6C, 0x24, 0x18, 0x56, 0x48, 0x83, 0xEC, 0x30, 0x48, 0x8B, 0x0D, 0xCC, 0xCC, 0xCC, 0xCC},
        &_CShutdownState_Run, 1);

    auto result = CShutdownState_Run.Attach();
    if (result != NO_ERROR)
    {
        auto message = fmt::format(L"Could not attach hook for CShutdownState::Run, attach returned {}.", result);
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONERROR | MB_OK);
    }
}

void CShutdownState::Detach()
{
    CShutdownState_Run.Detach();
}
