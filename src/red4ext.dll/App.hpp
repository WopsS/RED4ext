#pragma once

#include "Config.hpp"
#include "DevConsole.hpp"
#include "Paths.hpp"
#include "Systems/PluginSystem.hpp"

class App
{
public:
    ~App() = default;

    static void Construct();
    static void Destruct();
    static App* Get();

    void Startup();
    void Shutdown();

private:
    App();

    bool AttachHooks() const;

    Paths m_paths;
    Config m_config;
    DevConsole m_devConsole;
    PluginSystem m_pluginSystem;
};
