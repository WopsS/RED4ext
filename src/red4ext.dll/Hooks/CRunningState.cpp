#include <stdafx.hpp>
#include <Hooks/CRunningState.hpp>

#include <App.hpp>
#include <REDs/REDhook.hpp>

namespace
{
    bool CRunningState_Run(uintptr_t aThis, uintptr_t aApp);
    RED4ext::REDhook<decltype(&CRunningState_Run)> CRunningState_Run_h({ 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B,
                                                                         0x0D, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0x8B,
                                                                         0xDA },
                                                                       &CRunningState_Run, 4, 2);

    bool CRunningState_Run(uintptr_t aThis, uintptr_t aApp)
    {
        using Callback = RED4ext::PluginManager::Callback;
        auto result = CRunningState_Run_h(aThis, aApp);
        auto app = RED4ext::App::Get();

        auto pluginManager = app->GetPluginManager();
        pluginManager->Call(Callback::OnUpdate);

        return result;
    }
}

void RED4ext::Hooks::CRunningState::Attach()
{
    CRunningState_Run_h.Attach();
}

void RED4ext::Hooks::CRunningState::Detach()
{
    CRunningState_Run_h.Detach();
}
