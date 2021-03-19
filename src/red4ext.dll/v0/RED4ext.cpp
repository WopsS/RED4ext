#include "stdafx.hpp"
#include "RED4ext.hpp"
#include "App.hpp"
#include "Utils.hpp"

const RED4ext::v0::VersionInfo* v0::GetSDKVersion()
{
    static const RED4ext::v0::VersionInfo version = RED4EXT_SDK_LATEST;
    return &version;
}

const RED4ext::v0::VersionInfo* v0::GetRuntimeVersion()
{
    static const RED4ext::v0::VersionInfo version = []() {
        const auto version = Utils::GetRuntimeVersion();
        return RED4EXT_V0_SEMVER(version.major, version.minor, version.patch);
    }();

    return &version;
}

void v0::RegisterInterface(RED4ext::PluginHandle aHandle, void* aInterface)
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();

    auto plugin = manager->GetPlugin(aHandle);
    if (plugin)
    {
        plugin->SetInterface(aInterface);
    }
}

void* v0::GetInterface(const wchar_t* aName)
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();

    auto plugin = manager->GetPlugin(aName);
    if (plugin)
    {
        return plugin->GetInterface();
    }

    return nullptr;
}

const RED4ext::v0::IHooking* v0::GetHookingInterface()
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();
    return manager->GetV0Hooking();
}

const RED4ext::v0::ITrampoline* v0::GetTrampolineInterface()
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();
    return manager->GetV0Trampoline();
}
