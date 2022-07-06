#pragma once

namespace States::BaseInitializationState
{
bool OnEnter(RED4ext::CBaseInitializationState* aThis, RED4ext::CGameApplication* aApp);
bool OnUpdate(RED4ext::CBaseInitializationState* aThis, RED4ext::CGameApplication* aApp);
bool OnExit(RED4ext::CBaseInitializationState* aThis, RED4ext::CGameApplication* aApp);

bool Attach(RED4ext::CBaseInitializationState* aState);
bool Detach(RED4ext::CBaseInitializationState* aState);
} // namespace States::BaseInitializationState
