#include "stdafx.hpp"
#include "PluginManager.hpp"
#include "Utils.hpp"

PluginManager::PluginManager()
{
}

PluginManager::~PluginManager()
{
    UnloadAll();
}

void PluginManager::LoadAll(const std::filesystem::path& aPluginsDir)
{
    std::vector<std::filesystem::path> pluginPaths;
    m_logger = spdlog::default_logger();

    if (!std::filesystem::exists(aPluginsDir))
    {
        std::filesystem::create_directories(aPluginsDir);
    }

    for (auto& path : std::filesystem::directory_iterator(aPluginsDir))
    {
        if (path.path().extension() == L".dll")
        {
            pluginPaths.emplace_back(path);
        }
    }

    for (const auto& path : pluginPaths)
    {
        Load(path);
    }
}

void PluginManager::UnloadAll()
{
    for (const auto& plugin : m_plugins)
    {
        Unload(plugin);
    }

    m_plugins.clear();
}

void PluginManager::Load(const std::filesystem::path& aPath)
{
    if (aPath.extension() != L".dll")
    {
        return;
    }

    Plugin plugin;
    auto filename = aPath.filename();

    auto handle = LoadLibrary(aPath.c_str());
    if (!handle)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::warn(L"'{}' could not be loaded, error: 0x{:X}, description: {}", filename.c_str(), err, errMsg);
        return;
    }

    auto supports = reinterpret_cast<Supports_t>(GetProcAddress(handle, "Supports"));
    if (!supports)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::warn(L"'{}' could not be loaded, error: 0x{:X}, description: {}", filename.c_str(), err, errMsg);
        FreeLibrary(handle);

        return;
    }

    uint32_t apiVersion;
    bool success = false;

    try
    {
        apiVersion = supports();
        success = true;
    }
    catch (...)
    {
        spdlog::warn(L"An error occured while trying to get API version of '{}', the plugin will not be loaded",
                     filename.c_str());
    }

    if (!success)
    {
        FreeLibrary(handle);
        return;
    }

    if (apiVersion < MINIMUM_API_VERSION || apiVersion > LATEST_API_VERSION)
    {
        spdlog::warn(L"'{}' reported unsupported API version ({})", filename.c_str(), apiVersion);
        FreeLibrary(handle);

        return;
    }

    plugin.SetApiVersion(apiVersion);
    plugin.SetHandle(handle);

    auto query = reinterpret_cast<Query_t>(GetProcAddress(handle, "Query"));
    if (!query)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::debug(L"Could not retrieve 'Query' function from '{}', error: 0x{:X}, description: {}",
                      filename.c_str(), err, errMsg);
        FreeLibrary(handle);

        return;
    }

    success = false;
    try
    {
        query(plugin.GetInfo());
        success = true;
    }
    catch (...)
    {
        spdlog::warn(L"An exception occured while querying '{}', the plugin will not be loaded", filename.c_str());
    }

    if (!success)
    {
        FreeLibrary(handle);
        return;
    }

    if (plugin.GetName().empty())
    {
        spdlog::warn(L"'{}' did not supply a name, the plugin will not be loaded", filename.c_str());
        FreeLibrary(handle);

        return;
    }

    if (!plugin.IsCompatibleRuntime())
    {
        auto runtime = v1::GetRuntimeVersion();
        spdlog::warn(
            L"{} ({}) is not compatible with the current game version ({}.{:02d}), the compatible version is {}",
            plugin.GetName(), plugin.GetVersion(), runtime->major, runtime->minor, plugin.GetRuntime());
        FreeLibrary(handle);

        return;
    }

    auto load = reinterpret_cast<Load_t>(GetProcAddress(handle, "Load"));
    if (!load)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::debug(L"Could not retrieve 'Load' function from {}, error: 0x{:X}, description: {}", plugin.GetName(),
                      err, errMsg);
        return;
    }

    success = false;
    try
    {
        auto red4ext = plugin.GetInterface();

        if (!load(plugin.GetHandle(), &red4ext))
        {
            spdlog::warn(L"{} could not be loaded, 'Load' returned false", plugin.GetName());
            Unload(plugin);

            return;
        }

        success = true;
    }
    catch (...)
    {
        spdlog::warn(L"An error occured while loading {}, the plugin will not be loaded", plugin.GetName());
    }

    if (!success)
    {
        FreeLibrary(handle);
        return;
    }

    spdlog::info(L"{} (version: {}, author: {}) loaded", plugin.GetName(), plugin.GetVersion(), plugin.GetAuthor());
    m_plugins.emplace_back(std::move(plugin));
}

void PluginManager::Unload(const Plugin& aPlugin)
{
    auto handle = aPlugin.GetRawHandle();
    auto unload = reinterpret_cast<Unload_t>(GetProcAddress(handle, "Unload"));

    if (unload)
    {
        try
        {
            unload();
            m_logger->info(L"{} unloaded", aPlugin.GetName());
        }
        catch (...)
        {
            spdlog::warn(L"An error occured while unloading '{}'. This does not affect unloading this plugin, but if "
                         L"you are the plugin author you might want to fix this",
                         aPlugin.GetName());
        }
    }

    FreeLibrary(handle);
}
