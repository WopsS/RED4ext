#include "stdafx.hpp"
#include "Plugin.hpp"
#include "Api.hpp"

#include <RED4ext/Api/v1/Runtime.hpp>

#define THROW_UNHANDLED_API()                                                                                          \
    spdlog::error("The plugin API version ({}) is not handled, this should not happen, the process will now close to " \
                  "prevent unexpected behavior",                                                                       \
                  m_apiVersion);                                                                                       \
                                                                                                                       \
    throw std::runtime_error("API version not handled")

Plugin::Plugin()
    : m_apiVersion(0)
    , m_handle{}
    , m_info{}
{
}

void Plugin::SetApiVersion(uint32_t aVersion)
{
    assert(aVersion >= MINIMUM_API_VERSION && aVersion <= LATEST_API_VERSION);
    m_apiVersion = aVersion;
}

IRED4ext Plugin::GetInterface()
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);

    IRED4ext result;
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        result.v1.GetSDKVersion = &v1::GetSDKVersion;
        result.v1.GetRuntimeVersion = &v1::GetRuntimeVersion;

        break;
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }

    return result;
}

PluginHandle Plugin::GetHandle() const
{
    return m_handle;
}

HMODULE Plugin::GetRawHandle() const
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        return m_handle.v1;
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }
}

void Plugin::SetHandle(HMODULE aModule)
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        m_handle.v1 = aModule;
        break;
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }
}

std::wstring_view Plugin::GetName() const
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        return m_info.v1.name;
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }
}

std::wstring_view Plugin::GetAuthor() const
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);

    const wchar_t* author = nullptr;
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        author = m_info.v1.author;
        break;
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }

    if (author)
    {
        return author;
    }

    return L"Unknown";
}

std::wstring Plugin::GetVersion() const
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        return std::to_wstring(m_info.v1.version);
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }
}

std::wstring Plugin::GetRuntime() const
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        auto& runtime = m_info.v1.runtime;
        return fmt::format(L"{}.{}{}", runtime.major, runtime.minor, runtime.patch);
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }
}

bool Plugin::IsCompatibleRuntime() const
{
    assert(m_apiVersion >= MINIMUM_API_VERSION && m_apiVersion <= LATEST_API_VERSION);
    switch (m_apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        auto& requestedRuntime = m_info.v1.runtime;
        if (requestedRuntime == RED4EXT_V1_RUNTIME_INDEPENDENT)
        {
            return true;
        }

        auto runtime = v1::GetRuntimeVersion();

        return *runtime == requestedRuntime;
    }
    default:
    {
        THROW_UNHANDLED_API();
    }
    }
}

PluginInfo* Plugin::GetInfo()
{
    return &m_info;
}
