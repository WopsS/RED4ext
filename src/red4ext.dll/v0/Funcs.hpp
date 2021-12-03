#pragma once

namespace v0
{
bool AddState(RED4ext::PluginHandle aHandle, RED4ext::EGameStateType aType, RED4ext::GameState* aState);

namespace Hooking
{
bool Attach(RED4ext::PluginHandle aHandle, void* aTarget, void* aDetour, void** aOriginal);
bool Detach(RED4ext::PluginHandle aHandle, void* aTarget);
}
} // namespace v0
