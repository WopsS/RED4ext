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
            std::scoped_lock _(m_mutex);
            m_paths.emplace(aPlugin, std::move(resolvedPath));
            return true;
        }
        else
        {
            spdlog::trace(L"Could not find absolute path: {}", resolvedPath.c_str());
            return false;
        }
    } else {
        resolvedPath = aPlugin->GetPath() / aPath;
        if (std::filesystem::exists(resolvedPath))
        {
            spdlog::trace(L"Found path relative to plugin: {}", resolvedPath.c_str());
            std::scoped_lock _(m_mutex);
            m_paths.emplace(aPlugin, std::move(resolvedPath));
            return true;
        }
        else
        {
            spdlog::trace(L"Could not find path relative to plugin: {}", resolvedPath.c_str());
            return false;
        }
    }
}

std::vector<std::filesystem::path> ScriptSystem::GetPaths() {
    auto paths = std::vector<std::filesystem::path>();
    for (auto it = m_paths.begin(); it != m_paths.end(); ++it) {
        paths.emplace_back(it->second);
    }
    return paths;
}
