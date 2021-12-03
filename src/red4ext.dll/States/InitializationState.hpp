#pragma once

namespace States::InitializationState
{
bool OnEnter(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp);
bool OnUpdate(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp);
bool OnExit(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp);

bool Attach(RED4ext::CInitializationState* aState);
bool Detach(RED4ext::CInitializationState* aState);
} // namespace States::InitializationState
