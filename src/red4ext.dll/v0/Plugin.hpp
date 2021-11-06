#pragma once

#include "PluginBase.hpp"

namespace v0
{
class Plugin : public PluginBase
{
public:
    Plugin(const std::filesystem::path& aPath, wil::unique_hmodule aModule);

    const uint32_t GetApiVersion() const final;
    void* GetPluginInfo() final;
    const void* GetRedStruct() final;

    virtual const std::wstring_view GetName() const final;
    virtual const std::wstring_view GetAuthor() const final;
    virtual const RED4ext::VersionInfo& GetVersion() const final;
    virtual const RED4ext::VersionInfo& GetRuntimeVersion() const final;
    virtual const RED4ext::VersionInfo& GetSdkVersion() const final;

private:
    RED4ext::v0::PluginInfo m_info;
    RED4ext::v0::RED4ext m_red;
};
} // namespace v0
