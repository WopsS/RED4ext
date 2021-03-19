#pragma once

#include "REDhook.hpp"

class PluginBase
{
public:
    PluginBase(RED4ext::PluginHandle aHandle);
    virtual ~PluginBase() = default;

    RED4ext::PluginHandle GetHandle() const;

    virtual void* GetInfoHolder() = 0;

    virtual const std::wstring_view GetName() const = 0;
    virtual const std::wstring_view GetAuthor() const = 0;

    virtual const RED4ext::VersionInfo GetVersion() const = 0;
    virtual const RED4ext::VersionInfo GetRuntime() const = 0;
    virtual const RED4ext::VersionInfo GetSdk() const = 0;

    void SetInterface(void* aInterface);
    void* GetInterface() const;

private:
    RED4ext::PluginHandle m_handle;
    void* m_interface;
};
