#include "stdafx.hpp"
#include "Hooks/CShutdownState.hpp"
#include "App.hpp"
#include "REDhook.hpp"

#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameStates.hpp>

namespace
{
bool CShutdownState_Run(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp);
REDhook<decltype(&CShutdownState_Run)> CShutdownState_Run_h({0x48, 0x89, 0x6C, 0x24, 0x18, 0x56, 0x48, 0x83, 0xEC, 0x30,
                                                             0x48, 0x8B, 0x0D, 0xCC, 0xCC, 0xCC, 0xCC},
                                                            &CShutdownState_Run, 1);

bool CShutdownState_Run(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto pluginManager = app->GetPluginManager();

    pluginManager->UnloadAll();
    return CShutdownState_Run_h(aThis, aApp);
}
} // namespace

void CShutdownState::Attach()
{
    CShutdownState_Run_h.Attach();
}

void CShutdownState::Detach()
{
    CShutdownState_Run_h.Detach();
}
