#pragma once

#include <PluginManager.hpp>

namespace RED4ext
{
    class App
    {
    public:
        App() = default;
        ~App() = default;

        static App* Get();

        void Init(HMODULE aModule);
        void Run();
        void Shutdown();

        PluginManager* GetPluginManager();

    private:
        std::tuple<std::error_code, std::filesystem::path> GetDocumentsPath();
        void InitializeLogger(std::filesystem::path aRoot);

        PluginManager m_pluginManager;
    };
}
