#pragma once

namespace v1::Hooking
{
void Create(RED4ext::PluginHandle aHandle, void* aTarget, void* aDetour, void** aOriginal);
void Remove(RED4ext::PluginHandle aHandle, void* aTarget);

bool Attach(RED4ext::PluginHandle aHandle, void* aTarget);
bool Detach(RED4ext::PluginHandle aHandle, void* aTarget);

void* FindPattern(uint8_t* aPattern, size_t aPatternSize, uint8_t aWildcard, size_t aExpectedMatches, size_t aIndex);
} // namespace v1::Hooking
