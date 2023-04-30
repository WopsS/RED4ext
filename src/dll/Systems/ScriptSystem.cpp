#include "ScriptSystem.hpp"
#include "stdafx.hpp"

ScriptSystem::ScriptSystem(const Paths& aPaths)
    : m_paths(aPaths)
{
}

ESystemType ScriptSystem::GetType()
{
    return ESystemType::Script;
}

void ScriptSystem::Startup()
{
}

void ScriptSystem::Shutdown()
{
}

void ScriptSystem::SetScriptsBlobPath(RED4ext::CString* aScriptsBlobPath)
{
    m_scriptsBlobPath = *aScriptsBlobPath;
}

RED4ext::CString* ScriptSystem::GetScriptsBlobPath()
{
    return &m_scriptsBlobPath;
}

void ScriptSystem::SetUsingRedmod(bool aUsing)
{
    m_usingRedmod = aUsing;
}

bool ScriptSystem::IsUsingRedmod()
{
    return m_usingRedmod;
}

bool ScriptSystem::Add(std::shared_ptr<PluginBase> aPlugin, const char* aPath)
{
    spdlog::trace("Adding path to script compilation: '{}'", aPath);
    auto resolvedPath = std::filesystem::path(aPath);
    if (resolvedPath.is_absolute())
    {
        if (std::filesystem::exists(resolvedPath))
        {
            spdlog::trace(L"Found absolute path: {}", resolvedPath.wstring().c_str());
            return _Add(aPlugin, &resolvedPath);
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
            return _Add(aPlugin, &resolvedPath);
        }
        else
        {
            spdlog::error(L"Could not find path relative to plugin: {}", resolvedPath.wstring().c_str());
            return false;
        }
    }
}

bool ScriptSystem::_Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path* aPath)
{
    std::scoped_lock _(m_mutex);
    m_scriptPaths.emplace(aPlugin, std::move(*aPath));
    return true;
}

std::wstring ScriptSystem::CreatePathsFile() {
    auto scriptPaths = std::vector<std::filesystem::path>();
    for (auto it = m_scriptPaths.begin(); it != m_scriptPaths.end(); ++it)
    {
        scriptPaths.emplace_back(it->second);
    }
    spdlog::info("Adding paths to redscript compilation:");

    auto pathsFilePath = m_paths.GetRED4extDir() / "redscript_paths.txt";
    std::wofstream pathsFile;
    pathsFile.open(pathsFilePath);
    for (auto& path : scriptPaths)
    {
        spdlog::info(L"  '{}'", path.wstring());
        pathsFile << path.wstring() + L'\n';
    }
    pathsFile.close();
    spdlog::info(L"Paths written to: '{}'", pathsFilePath.wstring());
    return pathsFilePath.wstring();
}

std::wstring ScriptSystem::GetRedModArgs()
{
    return L"-compile \"" + (m_paths.GetRootDir() / "r6" / "scripts").wstring() + 
           L"\" -customCacheDir \"" + 
           (m_paths.GetRootDir() / "r6" / "cache" / "modded").wstring() + L"\"";
}
