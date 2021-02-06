#pragma once

#include "PluginManager.hpp"

class App
{
public:
    static void Construct(HMODULE aModule);
    static App* Get();

    void Init();
    void Shutdown();

    PluginManager* GetPluginManager();

    std::filesystem::path GetRootDirectory();
    std::filesystem::path GetPluginsDirectory();
    std::filesystem::path GetExecutablePath();

private:
    friend struct std::unique_ptr<App>::deleter_type;

    App(HMODULE aModule);
    ~App() = default;

    void CreateLogger();

    static std::unique_ptr<App> m_instance;

    HMODULE m_module;
    PluginManager m_pluginManager;
};
