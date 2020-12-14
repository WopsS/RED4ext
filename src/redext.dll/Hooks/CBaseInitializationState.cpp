#include <stdafx.hpp>
#include <Hooks/CBaseInitializationState.hpp>

#include <App.hpp>
#include <REDs/REDhook.hpp>

namespace
{
    bool CBaseInitializationState_Init(uintptr_t aThis, uintptr_t aApp);
    REDext::REDhook<decltype(&CBaseInitializationState_Init)> CBaseInitializationState_Init_h(
      { 0x48, 0x83, 0xEC, 0x28, 0x48, 0x8B, 0x05, 0xCC, 0xCC, 0xCC, 0xCC,
        0x4C, 0x8B, 0xC2, 0x48, 0x85, 0xC0, 0x75, 0x12, 0x8D, 0x50, 0x03 },
      &CBaseInitializationState_Init, 1);

    bool CBaseInitializationState_Init(uintptr_t aThis, uintptr_t aApp)
    {
        using Callback = REDext::PluginManager::Callback;
        auto result = CBaseInitializationState_Init_h(aThis, aApp);
        auto app = REDext::App::Get();

        auto pluginManager = app->GetPluginManager();
        pluginManager->Call(Callback::OnBaseInitialization);

        return result;
    }
}

void REDext::Hooks::CBaseInitializationState::Attach()
{
    CBaseInitializationState_Init_h.Attach();
}

void REDext::Hooks::CBaseInitializationState::Detach()
{
    CBaseInitializationState_Init_h.Detach();
}
