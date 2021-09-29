#include "stdafx.hpp"
#include "CShutdownState.hpp"
#include "Addresses.hpp"
#include "Hook.hpp"

#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameStates.hpp>

namespace
{
bool isAttached = false;

bool _CShutdownState_Run(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp);
Hook<decltype(&_CShutdownState_Run)> CShutdownState_Run(Addresses::CShutdownState_Run, &_CShutdownState_Run);

bool _CShutdownState_Run(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp)
{
    return CShutdownState_Run(aThis, aApp);
}
} // namespace

bool Hooks::CShutdownState::Attach()
{
    spdlog::trace("Trying to attach the hook for the shutdown state...");

    auto result = CShutdownState_Run.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the shutdown state. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the shutdown state was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::CShutdownState::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the shutdown state...");

    auto result = CShutdownState_Run.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the shutdown state. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the shutdown state was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
