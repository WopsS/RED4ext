#include "stdafx.hpp"
#include "Config.hpp"
#include "Utils.hpp"

#define DEFAULT_TOML_EXCEPTION_MSG L"An exception occured while parsing the config file:\n\n{}\n\nFile: {}"

Config::Config(const Paths& aPaths)
    : m_version(0)
    , m_devConsole(false)
    , m_logLevel(spdlog::level::info)
    , m_flushOn(spdlog::level::err)
    , m_maxLogFiles(5)
    , m_maxLogFileSize(10)
{
    const auto file = aPaths.GetConfigFile();

    std::error_code err;
    if (std::filesystem::exists(file, err))
    {
        Load(file);
    }
    else if (err)
    {
        auto errVal = err.value();
        const auto& category = err.category();
        auto msg = category.message(errVal);

        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"An error occured while checking config file existence:\n{}\n\nFile: {}",
                                            Utils::Widen(msg));
    }
    else
    {
        Save(file);
    }
}

const size_t Config::GetVersion() const
{
    return m_version;
}

const bool Config::HasDevConsole() const
{
    return m_devConsole;
}

const spdlog::level::level_enum Config::GetLogLevel() const
{
    return m_logLevel;
}

const spdlog::level::level_enum Config::GetFlushLevel() const
{
    return m_flushOn;
}

const uint32_t Config::GetMaxLogFiles() const
{
    return m_maxLogFiles;
}

const uint32_t Config::GetMaxLogFileSize() const
{
    return m_maxLogFileSize;
}

void Config::Load(const std::filesystem::path& aFile)
{
    try
    {
        auto config = toml::parse(aFile);
        if (config.contains("version"))
        {
            auto version = toml::find<size_t>(config, "version");
            switch (version)
            {
            case 1:
            {
                LoadV1(config);
                break;
            }
            default:
            {
                SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("The config file does not have a valid version.\n\nFile: {}",
                                                    aFile);
                break;
            }
            }
        }
        else
        {
            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("The config file does not have a version.\n\nFile: {}", aFile);
        }
    }
    catch (const std::exception& e)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(DEFAULT_TOML_EXCEPTION_MSG, Utils::Widen(e.what()), aFile);
    }
}

void Config::Save(const std::filesystem::path& aFile)
{
    try
    {
        using ordered_value = toml::basic_value<toml::preserve_comments, tsl::ordered_map>;

        auto logLevel = spdlog::level::to_string_view(m_logLevel).data();
        auto flushOn = spdlog::level::to_string_view(m_flushOn).data();

        ordered_value config{{"version", LatestVersion},
                             {"console", m_devConsole},

                             {"logging", ordered_value{{"level", logLevel},
                                                       {"flush_on", flushOn},
                                                       {"max_files", m_maxLogFiles},
                                                       {"max_file_size", m_maxLogFileSize}}}};

        config.comments().push_back(
            " See https://wiki.redmodding.org/red4ext/getting-started/configuration for more options.");

        std::ofstream file(aFile, std::ios::out);
        file.exceptions(std::ostream::badbit | std::ostream::failbit);

        file << config;
    }
    catch (const std::exception& e)
    {
        SHOW_MESSAGE_BOX_FILE_LINE(MB_ICONWARNING | MB_OK,
                                   "An exception occured while saving the config file:\n\n{}\n\nFile: {}",
                                   Utils::Widen(e.what()), aFile);
    }
}

void Config::LoadV1(const toml::value& aConfig)
{
    // General
    m_version = 1;
    m_devConsole = toml::find_or(aConfig, "console", m_devConsole);

    // Logging
    auto levelName = toml::find_or(aConfig, "logging", "level", "");
    if (!levelName.empty())
    {
        auto level = spdlog::level::from_str(levelName);

        // If the level is set to off, but the requested level is not "off" then the user might mistyped the levels.
        // spdlog return "level::off" if there is no match.
        if (level == spdlog::level::off && levelName != "off")
        {
            level = m_logLevel;
        }

        m_logLevel = level;
    }

    levelName = toml::find_or(aConfig, "logging", "flush_on", "");
    if (!levelName.empty())
    {
        auto level = spdlog::level::from_str(levelName.data());

        // Do not allow flushing to be off.
        if (level == spdlog::level::off)
        {
            level = m_flushOn;
        }

        m_flushOn = level;
    }

    m_maxLogFiles = toml::find_or(aConfig, "logging", "max_files", m_maxLogFiles);
    if (m_maxLogFiles < 1)
    {
        m_maxLogFiles = 5;
    }

    m_maxLogFileSize = toml::find_or(aConfig, "logging", "max_file_size", m_maxLogFileSize);
    if (m_maxLogFileSize < 1)
    {
        m_maxLogFileSize = 10;
    }
}
