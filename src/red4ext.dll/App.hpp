#pragma once

#include "Config.hpp"
#include "DevConsole.hpp"
#include "Paths.hpp"
#include "Systems/HookingSystem.hpp"
#include "Systems/LoggerSystem.hpp"
#include "Systems/PluginSystem.hpp"
#include "Systems/StateSystem.hpp"

class App
{
public:
    ~App() = default;

    static void Construct();
    static void Destruct();
    static App* Get();

    void Startup();
    void Shutdown();

    LoggerSystem* GetLoggerSystem();
    HookingSystem* GetHookingSystem();
    StateSystem* GetStateSystem();
    PluginSystem* GetPluginSystem();

private:
    App();

    bool AttachHooks() const;

    Paths m_paths;
    Config m_config;
    DevConsole m_devConsole;

    LoggerSystem m_loggerSystem;
    HookingSystem m_hookingSystem;
    StateSystem m_stateSystem;
    PluginSystem m_pluginSystem;
};
