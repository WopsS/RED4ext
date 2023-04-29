#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "PluginBase.hpp"
#include "Paths.hpp"

class ScriptSystem : public ISystem
{
public:
    ScriptSystem(const Paths& aPaths);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, const char *path);
    std::vector<std::filesystem::path> GetPaths();
    void GetRedModArgs(wchar_t* args);

    static const uint32_t strLengthMax = 0x1000;
    bool usingRedmod = false;
    RED4ext::CString scriptsBlobPath;
    RED4ext::CBaseEngine* engine;

private:
    bool _Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path *path);
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

    const Paths& m_paths;
    std::mutex m_mutex;
    Map_t m_scriptPaths;
    uint32_t m_strLength = 241;
    const uint32_t m_additionalCommandLength = strlen(" -compile \"\"");
};
