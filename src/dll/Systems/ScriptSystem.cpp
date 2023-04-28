#include "stdafx.hpp"
#include "ScriptSystem.hpp"

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

bool ScriptSystem::Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path aPath)
{
    spdlog::trace(L"Adding path '{}' to script compilation for {}", aPath.c_str(), aPlugin->GetName());
    auto resolvedPath = aPath;
    if (resolvedPath.is_absolute())
    {
        if (std::filesystem::exists(resolvedPath))
        {
            spdlog::trace(L"Found absolute path: {}", resolvedPath.c_str());
            return _Add(aPlugin, resolvedPath);
        }
        else
        {
            spdlog::error(L"Could not find absolute path: {}", resolvedPath.c_str());
            return false;
        }
    } else {
        resolvedPath = aPlugin->GetPath() / aPath;
        if (std::filesystem::exists(resolvedPath))
        {
            spdlog::trace(L"Found path relative to plugin: {}", resolvedPath.c_str());
            return _Add(aPlugin, resolvedPath);
        }
        else
        {
            spdlog::error(L"Could not find path relative to plugin: {}", resolvedPath.c_str());
            return false;
        }
    }
}

bool ScriptSystem::_Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path aPath) {
    std::scoped_lock _(m_mutex);
    auto pathLength = m_additionalCommandLength + aPath.string().size();
    if (m_strLength + pathLength > m_strLengthMax) {
        spdlog::error("Additional path ({} in length) would make compile string too long", pathLength);
        return false;
    }
    m_strLength += pathLength;
    m_paths.emplace(aPlugin, std::move(aPath));
    return true;
}

std::vector<std::filesystem::path> ScriptSystem::GetPaths() {
    auto paths = std::vector<std::filesystem::path>();
    for (auto it = m_paths.begin(); it != m_paths.end(); ++it) {
        paths.emplace_back(it->second);
    }
    return paths;
}
