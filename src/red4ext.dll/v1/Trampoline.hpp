#pragma once

namespace v1::Trampoline
{
void* Alloc(RED4ext::PluginHandle aHandle);
void Free(RED4ext::PluginHandle aHandle, void* aAddress);
} // namespace v1::Trampoline
