#include "ScriptCompilationSystem.hpp"
#include "Utils.hpp"
#include <string>

ScriptCompilationSystem::ScriptCompilationSystem(const Paths& aPaths)
    : m_paths(aPaths)
    , m_hasScriptsBlob(false)
{
}

ESystemType ScriptCompilationSystem::GetType()
{
    return ESystemType::Script;
}

void ScriptCompilationSystem::Startup()
{
}

void ScriptCompilationSystem::Shutdown()
{
}

void ScriptCompilationSystem::Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path aPath)
{
    std::scoped_lock _(m_mutex);
    m_scriptPaths.emplace(aPlugin, std::move(aPath));
}

void ScriptCompilationSystem::SetScriptsBlob(const std::filesystem::path& aPath)
{
    m_scriptsBlobPath = aPath;
    m_hasScriptsBlob = true;
}

const std::filesystem::path& ScriptCompilationSystem::GetScriptsBlob() const
{
    return m_scriptsBlobPath;
}

bool ScriptCompilationSystem::HasScriptsBlob() const
{
    return m_hasScriptsBlob;
}

bool ScriptCompilationSystem::Add(std::shared_ptr<PluginBase> aPlugin, const wchar_t* aPath)
{
    spdlog::trace(L"Adding path to script compilation: '{}'", aPath);
    auto resolvedPath = std::filesystem::path(aPath);
    if (resolvedPath.is_absolute())
    {
        if (std::filesystem::exists(resolvedPath))
        {
            spdlog::trace(L"Found absolute path: {}", resolvedPath.wstring().c_str());
            Add(aPlugin, resolvedPath);
            return true;
        }
        else
        {
            spdlog::error(L"Could not find absolute path: {}", resolvedPath.wstring().c_str());
            return false;
        }
    }
    else
    {
        resolvedPath = aPlugin->GetPath().parent_path() / aPath;
        if (std::filesystem::exists(resolvedPath))
        {
            spdlog::trace(L"Found path relative to plugin: {}", resolvedPath.wstring().c_str());
            Add(aPlugin, resolvedPath);
            return true;
        }
        else
        {
            spdlog::error(L"Could not find path relative to plugin: {}", resolvedPath.wstring().c_str());
            return false;
        }
    }
}

std::wstring ScriptCompilationSystem::GetCompilationArgs(const FixedWString& aOriginal)
{
    fmt::wmemory_buffer buffer;
    if (m_hasScriptsBlob)
    {
        spdlog::info("Using scriptsBlobPath");
        format_to(std::back_inserter(buffer), LR"(-compile "{}" "{}")", m_paths.GetR6Scripts(), m_scriptsBlobPath);
    }
    else
    {
        format_to(std::back_inserter(buffer), aOriginal.str);
    }
    spdlog::info("Adding paths to redscript compilation:");
    auto pathsFilePath = m_paths.GetRedscriptPathsFile();
    std::wofstream pathsFile(pathsFilePath, std::ios::out);
    for (const auto& [plugin, path] : m_scriptPaths)
    {
        spdlog::info(L"{}: '{}'", plugin->GetName(), path);
        pathsFile << path.wstring() << std::endl;
    }
    spdlog::info(L"Paths written to: '{}'", pathsFilePath);
    format_to(std::back_inserter(buffer), LR"( -compilePathsFile "{}")", pathsFilePath);
    return fmt::to_string(buffer);
}

const ScriptCompilationSystem::Map_t& ScriptCompilationSystem::GetScriptPaths() const
{
    return m_scriptPaths;
}

SourceRefRepository& ScriptCompilationSystem::GetSourceRefRepository()
{
    return m_sourceRefs;
}

// This function avoids allocating strings that are already in the file set. File paths are reused
// a lot between definitions, so this saves a lot of memory. The returned string_view is
// always a copy owned by the repository.
std::string_view SourceRefRepository::RegisterSourceFile(std::string_view aPath)
{
    auto it = m_paths.find(aPath);
    if (it != m_paths.end())
    {
        return it->first;
    }

    auto ptr = std::make_unique<std::string>(aPath);
    std::string_view view = *ptr;
    m_paths.emplace(view, std::move(ptr));
    return view;
}

void SourceRefRepository::RegisterClass(std::string_view aName, SourceRef aRef)
{
    m_classes.emplace(aName, aRef);
}

void SourceRefRepository::RegisterProperty(std::string_view aName, std::string_view aParent, SourceRef aRef)
{
    m_fields.emplace(fmt::format("{}::{}", aParent, aName), aRef);
}

void SourceRefRepository::RegisterMethod(std::string_view aName, std::string_view aParent, SourceRef aRef)
{
    m_methods.emplace(fmt::format("{}::{}", aParent, aName), aRef);
}

void SourceRefRepository::RegisterFunction(std::string_view aName, SourceRef aRef)
{
    m_functions.emplace(aName, aRef);
}

const SourceRef& SourceRefRepository::GetClass(const char* aName) const
{
    return m_classes.at(aName);
}

const SourceRef& SourceRefRepository::GetProperty(const char* aName, const char* aParent) const
{
    return m_fields.at(fmt::format("{}::{}", aParent, aName));
}

const SourceRef& SourceRefRepository::GetMethod(const char* aName, const char* aParent) const
{
    return m_methods.at(fmt::format("{}::{}", aParent, aName));
}

const SourceRef& SourceRefRepository::GetFunction(const char* aName) const
{
    return m_functions.at(aName);
}
