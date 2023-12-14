#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"

struct FixedWString
{
    uint32_t length;
    uint32_t maxLength;
    const wchar_t* str;
};

struct SourceRef
{
    std::string_view file;
    size_t line;
};

struct Member
{
    std::string_view name;
    std::string_view parent;

    bool operator==(const Member& other) const
    {
        return (parent == other.parent && name == other.name);
    }
};

template<>
struct std::hash<Member>
{
    std::size_t operator()(const Member& k) const
    {
        return std::hash<std::string_view>()(k.name) ^ (std::hash<std::string_view>()(k.parent) << 1);
    }
};

class SourceRefRepository
{
public:
    SourceRefRepository() = default;
    SourceRefRepository(const SourceRefRepository&) = delete;

    std::string_view RegisterSourceFile(std::string_view aPath);

    void RegisterClass(std::string_view aName, SourceRef aRef);
    void RegisterProperty(std::string_view aName, std::string_view aParent, SourceRef aRef);
    void RegisterMethod(std::string_view aName, std::string_view aParent, SourceRef aRef);
    void RegisterFunction(std::string_view aName, SourceRef aRef);

    const SourceRef& GetClass(std::string_view aName) const;
    const SourceRef& GetProperty(std::string_view aName, std::string_view aParent) const;
    const SourceRef& GetMethod(std::string_view aName, std::string_view aParent) const;
    const SourceRef& GetFunction(std::string_view aName) const;

private:
    std::string_view InternString(std::string_view aString);

    std::unordered_map<std::string_view, std::unique_ptr<std::string>> m_internedStrings;

    std::unordered_map<std::string_view, SourceRef> m_classes;
    std::unordered_map<Member, SourceRef> m_fields;
    std::unordered_map<Member, SourceRef> m_methods;
    std::unordered_map<std::string_view, SourceRef> m_functions;
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
