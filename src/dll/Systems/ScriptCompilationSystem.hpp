#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"

class ScriptCompilationSystem : public ISystem
{
public:
    ScriptCompilationSystem(const Paths& aPaths);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, const wchar_t* aPath);
    std::wstring GetRedModArgs();
    void SetScriptsBlob(const std::filesystem::path& aPath);
    const std::filesystem::path& GetScriptsBlob() const;
    void SetUsingRedmod(bool);
    bool IsUsingRedmod() const;
    std::wstring CreatePathsFile();

private:
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

    bool Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path* path);

    const Paths& m_paths;

    std::mutex m_mutex;
    Map_t m_scriptPaths;
    bool m_usingRedmod;
    std::filesystem::path m_scriptsBlobPath;
};
