#pragma once

#include "PluginManager.hpp"

class App
{
public:
    static void Construct(HMODULE aModule);
    static App* Get();

    void Run();
    void Init();
    void Shutdown();

    PluginManager* GetPluginManager();

private:
    std::tuple<std::error_code, std::filesystem::path> GetDocumentsPath();
    void InitializeLogger(std::filesystem::path aRoot);
    friend struct std::unique_ptr<App>::deleter_type;

    App(HMODULE aModule);
    ~App() = default;

    static std::unique_ptr<App> m_instance;

    HMODULE m_module;
    PluginManager m_pluginManager;
};
