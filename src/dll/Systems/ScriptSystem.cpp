#include "stdafx.hpp"
#include "ScriptSystem.hpp"

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

bool ScriptSystem::Add(std::shared_ptr<PluginBase> aPlugin, const char *aPath)
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
    } else {
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

bool ScriptSystem::_Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path *aPath) {
    std::scoped_lock _(m_mutex);
    auto pathLength = m_additionalCommandLength + aPath->string().size();
    if (m_strLength + pathLength > ScriptSystem::strLengthMax) {
        spdlog::error("Additional path ({} in length) would make compile string too long", pathLength);
        return false;
    }
    m_strLength += pathLength;
    m_scriptPaths.emplace(aPlugin, std::move(*aPath));
    return true;
}

std::vector<std::filesystem::path> ScriptSystem::GetPaths() {
    auto paths = std::vector<std::filesystem::path>();
    for (auto it = m_scriptPaths.begin(); it != m_scriptPaths.end(); ++it) {
        paths.emplace_back(it->second);
    }
    return paths;
}

void ScriptSystem::GetRedModArgs(wchar_t * args) {
    wsprintf(args, 
        L"-compile \"%s\" "
        L"-customCacheDir \"%s\"",
        (m_paths.GetRootDir() / "r6" / "scripts").wstring().c_str(),
        (m_paths.GetRootDir() / "r6" / "cache" / "modded").wstring().c_str());
}
