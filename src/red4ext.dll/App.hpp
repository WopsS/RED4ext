#pragma once

#include "HookingManager.hpp"
#include "PluginsManager.hpp"
#include "TrampolinesManager.hpp"

class App
{
public:
    static void Construct(HMODULE aModule);
    static App* Get();

    void Init();
    void Shutdown();

    HookingManager* GetHookingManager();
    TrampolinesManager* GetTrampolinesManager();

    PluginsManager* GetPluginsManager();

    std::filesystem::path GetRootDirectory();
    std::filesystem::path GetPluginsDirectory();
    std::filesystem::path GetLogsDirectory();
    std::filesystem::path GetExecutablePath();

private:
    friend struct std::unique_ptr<App>::deleter_type;

    App(HMODULE aModule);
    ~App() = default;

    void CreateLogger();

    static std::unique_ptr<App> m_instance;

    HMODULE m_module;

    HookingManager m_hookingManager;
    TrampolinesManager m_trampolinesManager;

    PluginsManager m_pluginsManager;
};
