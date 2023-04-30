#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"

class ScriptSystem : public ISystem
{
public:
    ScriptSystem(const Paths& aPaths);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, const char* path);
    std::wstring GetRedModArgs();
    void SetScriptsBlobPath(RED4ext::CString*);
    RED4ext::CString* GetScriptsBlobPath();
    void SetUsingRedmod(bool);
    bool IsUsingRedmod();
    std::wstring CreatePathsFile();

private:
    bool _Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path* path);
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

    const Paths& m_paths;

    std::mutex m_mutex;
    Map_t m_scriptPaths;
    bool m_usingRedmod = false;
    RED4ext::CString m_scriptsBlobPath;
};
