#include "stdafx.hpp"
#include "Plugin.hpp"

v0::Plugin::Plugin(RED4ext::PluginHandle aHandle)
    : PluginBase(aHandle)
    , m_info{}
{
}

void* v0::Plugin::GetInfoHolder()
{
    return &m_info;
}

const std::wstring_view v0::Plugin::GetName() const
{
    return m_info.name;
}

const std::wstring_view v0::Plugin::GetAuthor() const
{
    return m_info.author;
}

const RED4ext::VersionInfo v0::Plugin::GetVersion() const
{
    return m_info.version;
}

const RED4ext::VersionInfo v0::Plugin::GetRuntime() const
{
    return m_info.runtime;
}

const RED4ext::VersionInfo v0::Plugin::GetSdk() const
{
    return m_info.sdk;
}
