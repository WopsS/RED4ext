#include "stdafx.hpp"
#include "CRunningState.hpp"
#include "Addresses.hpp"
#include "Hook.hpp"

#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameStates.hpp>

namespace
{
bool isAttached = false;

bool _CRunningState_Run(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp);
Hook<decltype(&_CRunningState_Run)> CRunningState_Run(Addresses::CRunningState_Run, &_CRunningState_Run);

bool _CRunningState_Run(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp)
{
    return CRunningState_Run(aThis, aApp);
}
} // namespace

bool Hooks::CRunningState::Attach()
{
    spdlog::trace("Trying to attach the hook for the running state...");

    auto result = CRunningState_Run.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the running state. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the running state was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::CRunningState::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the running state...");

    auto result = CRunningState_Run.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the running state. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the running state was detached");
    }

    isAttached = result != NO_ERROR;
    return isAttached;
}
