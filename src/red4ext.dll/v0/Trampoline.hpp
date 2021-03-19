#pragma once

namespace v0::Trampoline
{
void* Alloc(RED4ext::PluginHandle aHandle);
void Free(RED4ext::PluginHandle aHandle, void* aAddress);
} // namespace v0::Trampoline
