#pragma once

#include "Config.hpp"
#include "DevConsole.hpp"
#include "Paths.hpp"

class App
{
public:
    ~App() = default;

    static void Construct();
    static void Destruct();
    static App* Get();

    void Init();
    void Shutdown();

private:
    App();

    Paths m_paths;
    Config m_config;
    DevConsole m_devConsole;
};
