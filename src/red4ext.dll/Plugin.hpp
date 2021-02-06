#pragma once

#include <Api.hpp>

class Plugin
{
public:
    Plugin();
    ~Plugin() = default;

    void SetApiVersion(uint32_t aVersion);

    IRED4ext GetInterface();
    PluginInfo* GetInfo();

    PluginHandle GetHandle() const;
    HMODULE GetRawHandle() const;

    void SetHandle(HMODULE aModule);

    std::wstring_view GetName() const;
    std::wstring_view GetAuthor() const;
    std::wstring GetVersion() const;
    std::wstring GetRuntime() const;

    bool IsCompatibleRuntime() const;

private:
    uint32_t m_apiVersion;
    PluginHandle m_handle;
    PluginInfo m_info;
};
