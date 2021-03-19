#pragma once

namespace v1
{
const RED4ext::v1::VersionInfo* GetSDKVersion();
const RED4ext::v1::VersionInfo* GetRuntimeVersion();

void RegisterInterface(RED4ext::PluginHandle aHandle, void* aInterface);
void* GetInterface(const wchar_t* aName);

const RED4ext::v1::IHooking* GetHookingInterface();
const RED4ext::v1::ITrampoline* GetTrampolineInterface();
} // namespace v1
