#pragma once

#include <RED4ext/Api.hpp>

union IRED4ext
{
    RED4ext::v1::IRED4ext v1;
};

union PluginHandle
{
    RED4ext::v1::PluginHandle v1;
};

union PluginInfo
{
    RED4ext::v1::PluginInfo v1;
};

namespace v1
{
const RED4ext::v1::VersionInfo* GetSDKVersion();
const RED4ext::v1::VersionInfo* GetRuntimeVersion();
} // namespace v1

#define MINIMUM_API_VERSION RED4EXT_API_VERSION_1
#define LATEST_API_VERSION RED4EXT_API_VERSION_LATEST
