#include "stdafx.hpp"
#include "v0/Plugin.hpp"
#include "Image.hpp"
#include "v0/Funcs.hpp"

v0::Plugin::Plugin(const std::filesystem::path& aPath, wil::unique_hmodule aModule)
    : PluginBase(aPath, std::move(aModule))
    , m_info{}
    , m_red{}
{
    m_red.runtime = Image::Get()->GetVersion();
    m_red.hooking.Attach = v0::Hooking::Attach;
    m_red.hooking.Detach = v0::Hooking::Detach;
}

const uint32_t v0::Plugin::GetApiVersion() const
{
    return RED4EXT_API_VERSION_0;
}

void* v0::Plugin::GetPluginInfo()
{
    return &m_info;
}

const void* v0::Plugin::GetRedStruct()
{
    return &m_red;
}

const std::wstring_view v0::Plugin::GetName() const
{
    return m_info.name;
}

const std::wstring_view v0::Plugin::GetAuthor() const
{
    return m_info.author;
}

const RED4ext::VersionInfo& v0::Plugin::GetVersion() const
{
    return m_info.version;
}

const RED4ext::VersionInfo& v0::Plugin::GetRuntimeVersion() const
{
    return m_info.runtime;
}

const RED4ext::VersionInfo& v0::Plugin::GetSdkVersion() const
{
    return m_info.sdk;
}
