#include "ScriptSystem.hpp"
#include "stdafx.hpp"

ScriptSystem::ScriptSystem(const Paths& aPaths)
    : m_paths(aPaths)
    , m_usingRedmod(false)
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

void ScriptSystem::SetScriptsBlobPath(RED4ext::CString& aScriptsBlobPath)
{
    m_scriptsBlobPath = aScriptsBlobPath;
}

const RED4ext::CString& ScriptSystem::GetScriptsBlobPath() const
{
    return m_scriptsBlobPath;
}

void ScriptSystem::SetUsingRedmod(bool aUsing)
{
    m_usingRedmod = aUsing;
}

bool ScriptSystem::IsUsingRedmod() const
{
    return m_usingRedmod;
}

bool ScriptSystem::Add(std::shared_ptr<PluginBase> aPlugin, const wchar_t* aPath)
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

bool ScriptSystem::Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path* aPath)
{
    std::scoped_lock _(m_mutex);
    m_scriptPaths.emplace(aPlugin, std::move(*aPath));
    return true;
}

std::wstring ScriptSystem::CreatePathsFile()
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

std::wstring ScriptSystem::GetRedModArgs()
{
    wchar_t scriptsBlobPath[0x100];
    mbstowcs_s(nullptr, scriptsBlobPath, m_scriptsBlobPath.c_str(), m_scriptsBlobPath.Length());
    return L"-compile \"" + m_paths.GetR6Scripts().wstring() + L"\" \"" + scriptsBlobPath + L"\"";
}
