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
    const void* GetSdkStruct() const final;

    virtual const std::wstring_view GetName() const final;
    virtual const std::wstring_view GetAuthor() const final;
    virtual const RED4ext::SemVer& GetVersion() const final;
    virtual const RED4ext::FileVer& GetRuntimeVersion() const final;
    virtual const RED4ext::SemVer& GetSdkVersion() const final;

private:
    RED4ext::v0::PluginInfo m_info;

    RED4ext::v0::Sdk m_sdk;
    RED4ext::v0::SemVer m_runtime;
    RED4ext::v0::Logger m_logger;
    RED4ext::v0::Hooking m_hooking;
    RED4ext::v0::GameStates m_gameStates;
    RED4ext::v0::Scripts m_scripts;
};
} // namespace v0
