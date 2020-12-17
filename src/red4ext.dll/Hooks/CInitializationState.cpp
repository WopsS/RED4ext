#include <stdafx.hpp>
#include <Hooks/CInitializationState.hpp>

#include <App.hpp>
#include <REDs/REDhook.hpp>

namespace
{
    bool CInitializationState_Init(uintptr_t aThis, uintptr_t aApp);
    RED4ext::REDhook<decltype(&CInitializationState_Init)> CInitializationState_Init_h({ 0x40, 0x55, 0x48, 0x8D, 0x6C,
                                                                                         0x24, 0xA9, 0x48, 0x81, 0xEC,
                                                                                         0x90, 0x00, 0x00, 0x00, 0xE8,
                                                                                         0xCC, 0xCC, 0xCC, 0xCC },
                                                                                       &CInitializationState_Init, 1);

    bool CInitializationState_Init(uintptr_t aThis, uintptr_t aApp)
    {
        using Callback = RED4ext::PluginManager::Callback;
        auto result = CInitializationState_Init_h(aThis, aApp);
        auto app = RED4ext::App::Get();

        auto pluginManager = app->GetPluginManager();
        pluginManager->Call(Callback::OnInitialization);

        return result;
    }
}

void RED4ext::Hooks::CInitializationState::Attach()
{
    CInitializationState_Init_h.Attach();
}

void RED4ext::Hooks::CInitializationState::Detach()
{
    CInitializationState_Init_h.Detach();
}
