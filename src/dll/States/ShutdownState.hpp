#pragma once

namespace States::ShutdownState
{
bool OnEnter(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp);
bool OnUpdate(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp);
bool OnExit(RED4ext::CShutdownState* aThis, RED4ext::CGameApplication* aApp);

bool Attach(RED4ext::CShutdownState* aState);
bool Detach(RED4ext::CShutdownState* aState);
} // namespace States::ShutdownState
