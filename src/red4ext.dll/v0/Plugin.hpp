#pragma once

#include "PluginBase.hpp"

namespace v0
{
class Plugin : public PluginBase
{
public:
    Plugin(RED4ext::PluginHandle aHandle);

    virtual void* GetInfoHolder() final;

    const std::wstring_view GetName() const final;
    const std::wstring_view GetAuthor() const final;

    const RED4ext::VersionInfo GetVersion() const final;
    const RED4ext::VersionInfo GetRuntime() const final;
    const RED4ext::VersionInfo GetSdk() const final;

private:
    RED4ext::v0::PluginInfo m_info;
};
} // namespace v1
