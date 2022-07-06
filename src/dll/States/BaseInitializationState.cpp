#include "stdafx.hpp"
#include "BaseInitializationState.hpp"
#include "App.hpp"
#include "GameStateHook.hpp"

namespace
{
GameStateHook<RED4ext::CBaseInitializationState> CBaseInitializationState(&States::BaseInitializationState::OnEnter,
                                                                          &States::BaseInitializationState::OnUpdate,
                                                                          &States::BaseInitializationState::OnExit);
}

bool States::BaseInitializationState::OnEnter(RED4ext::CBaseInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    auto result = CBaseInitializationState.OnEnter(aThis, aApp);
    stateSystem->OnEnter(RED4ext::EGameStateType::BaseInitialization, aApp);

    return result;
}

bool States::BaseInitializationState::OnUpdate(RED4ext::CBaseInitializationState* aThis,
                                               RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    auto result = CBaseInitializationState.OnUpdate(aThis, aApp);
    result = stateSystem->OnUpdate(RED4ext::EGameStateType::BaseInitialization, aApp) && result;

    /*
     * Doing this because the game might call "SetState" which will also change the application status and will force
     * the state to move on.
     */
    if (!result)
    {
        aApp->status = RED4ext::EGameStateStatus::Initialized;
        return false;
    }

    aApp->status = RED4ext::EGameStateStatus::Ran;
    return true;
}

bool States::BaseInitializationState::OnExit(RED4ext::CBaseInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    stateSystem->OnExit(RED4ext::EGameStateType::BaseInitialization, aApp);
    return CBaseInitializationState.OnExit(aThis, aApp);
}

bool States::BaseInitializationState::Attach(RED4ext::CBaseInitializationState* aState)
{
    return CBaseInitializationState.AttachAt(aState);
}

bool States::BaseInitializationState::Detach(RED4ext::CBaseInitializationState* aState)
{
    return CBaseInitializationState.DetachAt(aState);
}
