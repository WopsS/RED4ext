#pragma once

#include <Launchers/BaseLauncher.hpp>

namespace RED4ext
{
    class App
    {
    public:
        App() = default;
        ~App() = default;

        std::error_code Init();
        std::error_code Run(wchar_t* aCmdLine);
        std::error_code Shutdown();

    private:
        std::tuple<std::error_code, std::filesystem::path> GetDocumentsPath();
        void InitializeLogger(std::filesystem::path aRoot);

        std::unique_ptr<Launchers::BaseLauncher> m_launcher;
    };
}
