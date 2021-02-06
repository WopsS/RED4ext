#pragma once

#include <Plugin.hpp>

class PluginManager
{
public:
    PluginManager();
    ~PluginManager();

    void LoadAll(const std::filesystem::path& aPluginsDir);
    void UnloadAll();

private:
    using Load_t = bool (*)(PluginHandle, const IRED4ext*);
    using Unload_t = void (*)();
    using Query_t = void (*)(PluginInfo*);
    using Supports_t = uint32_t (*)();

    void Load(const std::filesystem::path& aPath);
    void Unload(const Plugin& aPlugin);

    std::vector<Plugin> m_plugins;

    // Save an instance of the logger for printing unloading messages, the "Unload" method can be called after spdlog
    // release this instance if ref count is 0.
    std::shared_ptr<spdlog::logger> m_logger;
};
