#pragma once

namespace REDext
{
    class App
    {
    public:
        App() = default;
        ~App() = default;

        static App* Get();

        void Init();
        void Run();
        void Shutdown();

    private:
        std::tuple<std::error_code, std::filesystem::path> GetDocumentsPath();
        void InitializeLogger(std::filesystem::path aRoot);
    };
}
