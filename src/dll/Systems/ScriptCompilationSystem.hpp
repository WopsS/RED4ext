#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"
#include <RED4ext/RedProcess.hpp>

class ScriptCompilationSystem : public ISystem
{
public:
    ScriptCompilationSystem(const Paths& aPaths);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, const wchar_t* aPath);

    void SetScriptsBlob(const std::filesystem::path& aPath);
    const std::filesystem::path& GetScriptsBlob() const;

    std::wstring GetCompilationArgs(const RED4ext::red::Process::FixedWString& aOriginal);

    bool HasScripts() const;

private:
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

    void Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path path);

    const Paths& m_paths;

    std::mutex m_mutex;
    Map_t m_scriptPaths;
    bool m_hasScriptsBlob;
    std::filesystem::path m_scriptsBlobPath;
};
