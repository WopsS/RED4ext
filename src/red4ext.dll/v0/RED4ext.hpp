#pragma once

namespace v0
{
const RED4ext::v0::VersionInfo* GetSDKVersion();
const RED4ext::v0::VersionInfo* GetRuntimeVersion();

void RegisterInterface(RED4ext::PluginHandle aHandle, void* aInterface);
void* GetInterface(const wchar_t* aName);

const RED4ext::v0::IHooking* GetHookingInterface();
const RED4ext::v0::ITrampoline* GetTrampolineInterface();
} // namespace v1
