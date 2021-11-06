#pragma once

#include "Config.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"

class PluginSystem
{
public:
    PluginSystem(const Config::PluginsConfig& aConfig, const Paths& aPaths);
    ~PluginSystem() = default;

    void Startup();
    void Shutdown();

private:
    using Map_t = std::unordered_map<HMODULE, std::shared_ptr<PluginBase>>;
    using MapIter_t = std::unordered_map<HMODULE, std::shared_ptr<PluginBase>>::iterator;

    void Load(const std::filesystem::path& aPath, bool aSearchLoadDir);
    MapIter_t Unload(std::shared_ptr<PluginBase> aPlugin);

    std::shared_ptr<PluginBase> CreatePlugin(const std::filesystem::path& aPath, wil::unique_hmodule aModule) const;

    const Config::PluginsConfig& m_config;
    const Paths& m_paths;

    Map_t m_plugins;
};
