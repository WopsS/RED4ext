#include "stdafx.hpp"
#include "InitializationState.hpp"
#include "App.hpp"
#include "GameStateHook.hpp"

namespace
{
GameStateHook<RED4ext::CInitializationState> CInitializationState(&States::InitializationState::OnEnter,
                                                                  &States::InitializationState::OnUpdate,
                                                                  &States::InitializationState::OnExit);
}

bool States::InitializationState::OnEnter(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    auto result = CInitializationState.OnEnter(aThis, aApp);
    stateSystem->OnEnter(RED4ext::EGameStateType::Initialization, aApp);

    return result;
}

bool States::InitializationState::OnUpdate(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    auto result = CInitializationState.OnUpdate(aThis, aApp);
    result = stateSystem->OnUpdate(RED4ext::EGameStateType::Initialization, aApp) && result;

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

bool States::InitializationState::OnExit(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    stateSystem->OnExit(RED4ext::EGameStateType::Initialization, aApp);
    return CInitializationState.OnExit(aThis, aApp);
}

bool States::InitializationState::Attach(RED4ext::CInitializationState* aState)
{
    return CInitializationState.AttachAt(aState);
}

bool States::InitializationState::Detach(RED4ext::CInitializationState* aState)
{
    return CInitializationState.DetachAt(aState);
}
