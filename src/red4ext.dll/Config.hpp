#pragma once

#include "Paths.hpp"

class Config
{
public:
    static constexpr size_t LatestVersion = 0;
    static constexpr size_t MinSupportedVersion = 0;
    static constexpr size_t MaxSupportedVersion = 0;

    struct DevConfig
    {
        void LoadV0(const toml::value& aConfig);

        bool hasConsole = false;
        bool waitForDebugger = false;
    };

    struct LoggingConfig
    {
        void LoadV0(const toml::value& aConfig);

        spdlog::level::level_enum level = spdlog::level::info;
        spdlog::level::level_enum flushOn = spdlog::level::info;
        uint32_t maxFiles = 5;
        uint32_t maxFileSize = 10;
    };

    struct PluginsConfig
    {
        void LoadV0(const toml::value& aConfig);

        bool isEnabled = true;
        std::unordered_set<std::wstring> ignored;
    };

    Config(const Paths& aPaths);
    ~Config() = default;

    const size_t GetVersion() const;

    const DevConfig& GetDev() const;
    const LoggingConfig& GetLogging() const;
    const PluginsConfig& GetPlugins() const;

private:
    void Load(const std::filesystem::path& aFile);
    void Save(const std::filesystem::path& aFile);

    void LoadV0(const toml::value& aConfig);

    size_t m_version;

    DevConfig m_dev;
    LoggingConfig m_logging;
    PluginsConfig m_plugins;
};
