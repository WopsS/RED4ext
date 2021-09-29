#include "stdafx.hpp"
#include "CInitializationState.hpp"
#include "Addresses.hpp"
#include "Hook.hpp"

#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameStates.hpp>

namespace
{
bool isAttached = false;

bool _CInitializationState_Run(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp);
Hook<decltype(&_CInitializationState_Run)> CInitializationState_Run(Addresses::CInitializationState_Run,
                                                                    &_CInitializationState_Run);

bool _CInitializationState_Run(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    return CInitializationState_Run(aThis, aApp);
}
} // namespace

bool Hooks::CInitializationState::Attach()
{
    spdlog::trace("Trying to attach the hook for the initialization state...");

    auto result = CInitializationState_Run.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the initialization state. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the initialization state was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::CInitializationState::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the initialization state...");

    auto result = CInitializationState_Run.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the initialization state. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the initialization state was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
