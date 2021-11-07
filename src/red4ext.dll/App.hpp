#pragma once

#include "Config.hpp"
#include "DevConsole.hpp"
#include "Paths.hpp"
#include "Systems/PluginSystem.hpp"
#include "Systems/HookingSystem.hpp"

class App
{
public:
    ~App() = default;

    static void Construct();
    static void Destruct();
    static App* Get();

    void Startup();
    void Shutdown();

    HookingSystem* GetHookingSystem();
    PluginSystem* GetPluginSystem();

private:
    App();

    bool AttachHooks() const;

    Paths m_paths;
    Config m_config;
    DevConsole m_devConsole;
    HookingSystem m_hookingSystem;
    PluginSystem m_pluginSystem;
};
