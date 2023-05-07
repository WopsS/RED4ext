#include "ScriptCompilationSystem.hpp"
#include "stdafx.hpp"

ScriptCompilationSystem::ScriptCompilationSystem(const Paths& aPaths)
    : m_paths(aPaths)
    , m_usingRedmod(false)
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

void ScriptCompilationSystem::SetScriptsBlob(const std::filesystem::path& aPath)
{
    m_scriptsBlobPath = aPath;
}

const std::filesystem::path& ScriptCompilationSystem::GetScriptsBlob() const
{
    return m_scriptsBlobPath;
}

void ScriptCompilationSystem::SetUsingRedmod(bool aUsing)
{
    m_usingRedmod = aUsing;
}

bool ScriptCompilationSystem::IsUsingRedmod() const
{
    return m_usingRedmod;
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
            return Add(aPlugin, &resolvedPath);
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
            return Add(aPlugin, &resolvedPath);
        }
        else
        {
            spdlog::error(L"Could not find path relative to plugin: {}", resolvedPath.wstring().c_str());
            return false;
        }
    }
}

bool ScriptCompilationSystem::Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path* aPath)
{
    std::scoped_lock _(m_mutex);
    m_scriptPaths.emplace(aPlugin, std::move(*aPath));
    return true;
}

std::wstring ScriptCompilationSystem::CreatePathsFile()
{
    spdlog::info("Adding paths to redscript compilation:");

    auto pathsFilePath = m_paths.GetRedscriptPathsFile();
    std::wofstream pathsFile(pathsFilePath, std::ios::out);
    for (auto it = m_scriptPaths.begin(); it != m_scriptPaths.end(); ++it)
    {
        spdlog::info(L"{}: '{}'", it->first->GetName(), it->second.wstring());
        pathsFile << it->second.wstring() << std::endl;
    }
    spdlog::info(L"Paths written to: '{}'", pathsFilePath.wstring());
    return pathsFilePath.wstring();
}

std::wstring ScriptCompilationSystem::GetRedModArgs()
{
    return L"-compile \"" + m_paths.GetR6Scripts().wstring() + L"\" \"" + m_scriptsBlobPath.wstring() + L"\"";
}
