#pragma once

namespace RED4ext
{
    class PluginManager
    {
    public:
        enum class Callback : uint8_t
        {
            OnBaseInitialization,
            OnInitialization,
            OnUpdate,
            OnShutdown
        };

        PluginManager() = default;
        ~PluginManager() = default;

        void Init(HMODULE aModule, std::filesystem::path aDocsPath);
        void Shutdown();

        void Call(Callback aCallback);

    private:

        struct PluginInfo
        {
            std::wstring Name;
            HMODULE Module;

            std::function<void()> OnBaseInitialization;
            std::function<void()> OnInitialization;
            std::function<void()> OnUpdate;
            std::function<void()> OnShutdown;
        };

        std::vector<PluginInfo> m_plugins;
    };
}
