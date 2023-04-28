#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "PluginBase.hpp"

class ScriptSystem : public ISystem
{
public:
    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path path);
    std::vector<std::filesystem::path> GetPaths();

private:
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

    std::mutex m_mutex;
    Map_t m_paths;
};
