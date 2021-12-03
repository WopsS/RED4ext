#pragma once

namespace States::RunningState
{
bool OnEnter(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp);
bool OnUpdate(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp);
bool OnExit(RED4ext::CRunningState* aThis, RED4ext::CGameApplication* aApp);

bool Attach(RED4ext::CRunningState* aState);
bool Detach(RED4ext::CRunningState* aState);
} // namespace States::RunningState
