#pragma once

#include "Paths.hpp"

class Config
{
public:
    static constexpr size_t LatestVersion = 1;

    struct LoggingConfig
    {
        void LoadV1(const toml::value& aConfig);

        spdlog::level::level_enum level = spdlog::level::info;
        spdlog::level::level_enum flushOn = spdlog::level::err;
        uint32_t maxFiles = 5;
        uint32_t maxFileSize = 10;
    };

    struct PluginsConfig
    {
        void LoadV1(const toml::value& aConfig);

        bool isEnabled = true;
        std::unordered_set<std::wstring> blacklist;
    };

    Config(const Paths& aPaths);
    ~Config() = default;

    const size_t GetVersion() const;
    const bool HasDevConsole() const;

    const LoggingConfig& GetLogging() const;
    const PluginsConfig& GetPlugins() const;

private:
    void Load(const std::filesystem::path& aFile);
    void Save(const std::filesystem::path& aFile);

    void LoadV1(const toml::value& aConfig);

    size_t m_version;
    bool m_devConsole;

    LoggingConfig m_logging;
    PluginsConfig m_plugins;
};
