#include "stdafx.hpp"
#include "RunningState.hpp"
#include "App.hpp"
#include "GameStateHook.hpp"

namespace
{
GameStateHook<RED4ext::CRunningState> CRunningState(&States::RunningState::OnEnter, &States::RunningState::OnUpdate,
                                                    &States::RunningState::OnExit);
}

bool States::RunningState::OnEnter(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    auto result = CRunningState.OnEnter(aThis, aApp);
    stateSystem->OnEnter(RED4ext::EGameStateType::Running, aApp);

    return result;
}

bool States::RunningState::OnUpdate(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    auto result = CRunningState.OnUpdate(aThis, aApp);
    stateSystem->OnUpdate(RED4ext::EGameStateType::Running, aApp);

    return result;
}

bool States::RunningState::OnExit(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp)
{
    auto app = App::Get();
    auto stateSystem = app->GetStateSystem();

    stateSystem->OnExit(RED4ext::EGameStateType::Running, aApp);
    return CRunningState.OnExit(aThis, aApp);
}

bool States::RunningState::Attach(RED4ext::CRunningState* aState)
{
    return CRunningState.AttachAt(aState);
}

bool States::RunningState::Detach(RED4ext::CRunningState* aState)
{
    return CRunningState.DetachAt(aState);
}
