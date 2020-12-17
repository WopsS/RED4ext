#include <stdafx.hpp>
#include <PluginManager.hpp>

void RED4ext::PluginManager::Init(HMODULE aModule, std::filesystem::path aDocsPath)
{
    // Make sure we have the plugin directories and create a list of plugins to load.
    std::vector<std::filesystem::path> plugins;

    auto pluginsDir = aDocsPath / "plugins";
    if (!std::filesystem::exists(pluginsDir))
    {
        std::filesystem::create_directories(pluginsDir);
    }

    for (auto& path : std::filesystem::recursive_directory_iterator(pluginsDir))
    {
        if (path.path().extension() == L".dll")
        {
            plugins.emplace_back(path);
        }
    }

    std::filesystem::path currDir;
    {
        wchar_t pathPtr[MAX_PATH];
        GetModuleFileName(aModule, pathPtr, MAX_PATH);

        currDir = pathPtr;
        currDir = currDir.parent_path();
    }

    pluginsDir = currDir / "plugins";
    if (!std::filesystem::exists(pluginsDir))
    {
        std::filesystem::create_directories(pluginsDir);
    }

    for (auto& path : std::filesystem::directory_iterator(pluginsDir))
    {
        if (path.path().extension() == L".dll")
        {
            plugins.emplace_back(path);
        }
    }

    for (auto& path : plugins)
    {
        PluginInfo plugin{};
        plugin.Name = path.stem().wstring();
        plugin.Module = LoadLibrary(path.c_str());

        if (plugin.Module)
        {
            plugin.OnBaseInitialization = GetProcAddress(plugin.Module, "OnBaseInitialization");
            if (!plugin.OnBaseInitialization)
            {
                spdlog::debug(L"'{}' does not export 'OnBaseInitialization' function", plugin.Name);
            }

            plugin.OnInitialization = GetProcAddress(plugin.Module, "OnInitialization");
            if (!plugin.OnInitialization)
            {
                spdlog::debug(L"'{}' does not export 'OnInitialization' function", plugin.Name);
            }

            plugin.OnUpdate = GetProcAddress(plugin.Module, "OnUpdate");
            if (!plugin.OnUpdate)
            {
                spdlog::debug(L"'{}' does not export 'OnUpdate' function", plugin.Name);
            }

            plugin.OnShutdown = GetProcAddress(plugin.Module, "OnShutdown");
            if (!plugin.OnShutdown)
            {
                spdlog::debug(L"'{}' does not export 'OnShutdown' function", plugin.Name);
            }

            spdlog::info(L"'{}' loaded", plugin.Name);
            m_plugins.emplace_back(plugin);
        }
    }
}

void RED4ext::PluginManager::Shutdown()
{
    for (auto& plugin : m_plugins)
    {
        FreeLibrary(plugin.Module);
        spdlog::info(L"'{}' unloaded", plugin.Name);
    }
}

void RED4ext::PluginManager::Call(Callback aCallback)
{
    for (auto& plugin : m_plugins)
    {
        switch (aCallback)
        {
        case Callback::OnBaseInitialization:
        {
            if (plugin.OnBaseInitialization)
            {
                plugin.OnBaseInitialization();
            }

            break;
        }
        case Callback::OnInitialization:
        {
            if (plugin.OnInitialization)
            {
                plugin.OnInitialization();
            }

            break;
        }
        case Callback::OnUpdate:
        {
            if (plugin.OnUpdate)
            {
                plugin.OnUpdate();
            }

            break;
        }
        case Callback::OnShutdown:
        {
            if (plugin.OnShutdown)
            {
                plugin.OnShutdown();
            }

            break;
        }
        }
    }
}
