#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"
#include <cstdint>
#include <string>
#include <tsl/ordered_map.h>
#include <tsl/ordered_set.h>

struct FixedWString
{
    uint32_t length;
    uint32_t maxLength;
    const wchar_t* str;
};

struct SourceRef {
    std::string_view file;
    uint32_t line;
};

class SourceRefRepository {
public:
    SourceRefRepository() = default;
    SourceRefRepository(const SourceRefRepository&) = delete;

    std::string_view RegisterSourceFile(std::string_view aPath);

    void RegisterClass(std::string_view aName, SourceRef aRef);
    void RegisterProperty(std::string_view aName, std::string_view aParent, SourceRef aRef);
    void RegisterMethod(std::string_view aName, std::string_view aParent, SourceRef aRef);
    void RegisterFunction(std::string_view aName, SourceRef aRef);

    const SourceRef& GetClass(const char* aName) const;
    const SourceRef& GetProperty(const char* aName, const char* aParent) const;
    const SourceRef& GetMethod(const char* aName, const char* aParent) const;
    const SourceRef& GetFunction(const char* aName) const;

private:
    tsl::ordered_map<std::string_view, std::unique_ptr<std::string>> m_paths;

    tsl::ordered_map<std::string, SourceRef> m_classes;
    tsl::ordered_map<std::string, SourceRef> m_fields;
    tsl::ordered_map<std::string, SourceRef> m_methods;
    tsl::ordered_map<std::string, SourceRef> m_functions;
};

class ScriptCompilationSystem : public ISystem
{
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

public:
    ScriptCompilationSystem(const Paths& aPaths);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, const wchar_t* aPath);

    void SetScriptsBlob(const std::filesystem::path& aPath);
    const std::filesystem::path& GetScriptsBlob() const;
    bool HasScriptsBlob() const;

    std::wstring GetCompilationArgs(const FixedWString& aOriginal);
    const Map_t& GetScriptPaths() const;

    SourceRefRepository& GetSourceRefRepository();

private:
    void Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path path);

    const Paths& m_paths;

    std::mutex m_mutex;
    Map_t m_scriptPaths;
    bool m_hasScriptsBlob;
    std::filesystem::path m_scriptsBlobPath;
    SourceRefRepository m_sourceRefs;
};
