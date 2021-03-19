#include "stdafx.hpp"
#include "RED4ext.hpp"
#include "App.hpp"
#include "Utils.hpp"

const RED4ext::v1::VersionInfo* v1::GetSDKVersion()
{
    static const RED4ext::v1::VersionInfo version = RED4EXT_SDK_LATEST;
    return &version;
}

const RED4ext::v1::VersionInfo* v1::GetRuntimeVersion()
{
    static const RED4ext::v1::VersionInfo version = []() {
        const auto version = Utils::GetRuntimeVersion();
        return RED4EXT_V1_SEMVER(version.major, version.minor, version.patch);
    }();

    return &version;
}

void v1::RegisterInterface(RED4ext::PluginHandle aHandle, void* aInterface)
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();

    auto plugin = manager->GetPlugin(aHandle);
    if (plugin)
    {
        plugin->SetInterface(aInterface);
    }
}

void* v1::GetInterface(const wchar_t* aName)
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

const RED4ext::v1::IHooking* v1::GetHookingInterface()
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();
    return manager->GetV1Hooking();
}

const RED4ext::v1::ITrampoline* v1::GetTrampolineInterface()
{
    auto app = App::Get();
    auto manager = app->GetPluginsManager();
    return manager->GetV1Trampoline();
}
