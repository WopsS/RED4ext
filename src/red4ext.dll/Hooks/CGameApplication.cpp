#include "stdafx.hpp"
#include "CGameApplication.hpp"
#include "Addresses.hpp"
#include "Hook.hpp"

#include "States/BaseInitializationState.hpp"
#include "States/InitializationState.hpp"
#include "States/RunningState.hpp"
#include "States/ShutdownState.hpp"

namespace
{
bool isAttached = false;

bool _CGameApplication_Run(RED4ext::CGameApplication* aThis);
Hook<decltype(&_CGameApplication_Run)> CGameApplication_Run(Addresses::CGameApplication_Run, &_CGameApplication_Run);

bool _CGameApplication_Run(RED4ext::CGameApplication* aThis)
{
    bool success = true;
    try
    {
        if (aThis->states.size > 0)
        {
            spdlog::trace("Changing virtual functions for {} game state(s)...", aThis->states.size);

            for (auto state : aThis->states)
            {
                switch (state->GetType())
                {
                case RED4ext::EGameStateType::BaseInitialization:
                {
                    success = States::BaseInitializationState::Attach(
                                  static_cast<RED4ext::CBaseInitializationState*>(state)) &&
                              success;
                    break;
                }
                case RED4ext::EGameStateType::Initialization:
                {
                    success = States::InitializationState::Attach(static_cast<RED4ext::CInitializationState*>(state)) &&
                              success;
                    break;
                }
                case RED4ext::EGameStateType::Running:
                {
                    success = States::RunningState::Attach(static_cast<RED4ext::CRunningState*>(state)) && success;
                    break;
                }
                case RED4ext::EGameStateType::Shutdown:
                {
                    success = States::ShutdownState::Attach(static_cast<RED4ext::CShutdownState*>(state)) && success;
                    break;
                }
                default:
                {
                    spdlog::warn("State '{}' ({}) is not handled", state->GetName(), state->GetType());
                }
                }
            }

            if (success)
            {
                spdlog::trace("All virtual functions were changed successfully");
            }
            else
            {
                spdlog::warn(
                    "One or more game state virtual functions could not be changed, the game will continue running "
                    "but unexpected behavior might happen");
            }
        }
        else
        {
            spdlog::warn("No game states found, might be that the structure layout changed, check if a new RED4ext "
                         "version is available");
        }
    }
    catch (const std::exception& e)
    {
        spdlog::warn("An exception occured while changing the virtual functions for the game states");
        spdlog::warn(e.what());
    }
    catch (...)
    {
        spdlog::warn("An unknown exception occured while changing the virtual functions for the game states");
    }

    auto result = CGameApplication_Run(aThis);
    success = true;

    try
    {
        if (aThis->states.size > 0)
        {
            spdlog::trace("Restoring virtual functions for {} game state(s)...", aThis->states.size);

            for (auto state : aThis->states)
            {
                switch (state->GetType())
                {
                case RED4ext::EGameStateType::BaseInitialization:
                {
                    success = States::BaseInitializationState::Detach(
                                  static_cast<RED4ext::CBaseInitializationState*>(state)) &&
                              success;
                    break;
                }
                case RED4ext::EGameStateType::Initialization:
                {
                    success = States::InitializationState::Detach(static_cast<RED4ext::CInitializationState*>(state)) &&
                              success;
                    break;
                }
                case RED4ext::EGameStateType::Running:
                {
                    success = States::RunningState::Detach(static_cast<RED4ext::CRunningState*>(state)) && success;
                    break;
                }
                case RED4ext::EGameStateType::Shutdown:
                {
                    success = States::ShutdownState::Detach(static_cast<RED4ext::CShutdownState*>(state)) && success;
                    break;
                }
                default:
                {
                    spdlog::warn("State '{}' ({}) is not handled", state->GetName(), state->GetType());
                }
                }
            }

            if (success)
            {
                spdlog::trace("All virtual functions were restored successfully");
            }
            else
            {
                spdlog::warn(
                    "One or more game state virtual functions could not be restored, unexpected behavior might happen");
            }
        }
    }
    catch (const std::exception& e)
    {
        spdlog::warn("An exception occured while restoring the virtual functions for the game states");
        spdlog::warn(e.what());
    }
    catch (...)
    {
        spdlog::warn("An unknown exception occured while restoring the virtual functions for the game states");
    }

    return result;
}
} // namespace

bool Hooks::CGameApplication::Attach()
{
    spdlog::trace("Trying to attach the hook for the game application at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::CGameApplication_Run));

    auto result = CGameApplication_Run.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the game application. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the game application was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::CGameApplication::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the game application at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::CGameApplication_Run));

    auto result = CGameApplication_Run.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the game application. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the game application was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
