#include "stdafx.hpp"
#include "Config.hpp"
#include "Utils.hpp"

#define DEFAULT_TOML_EXCEPTION_MSG L"An exception occured while parsing the config file:\n\n{}\n\nFile: {}"

Config::Config(const Paths& aPaths)
    : m_devConsole(false)
    , m_logLevel(spdlog::level::info)
    , m_flushOn(spdlog::level::err)
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

void Config::Load(const std::filesystem::path& aFile)
{
    using namespace std::string_literals;

    try
    {
        toml::table config = toml::parse_file(aFile.c_str());

        // General.
        m_devConsole = config["console"].value_or(m_devConsole);

        // Logging.
        auto levelName = config["logging"]["level"].value_or(""s);
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

        levelName = config["logging"]["flush_on"].value_or(""s);
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
    }
    catch (const toml::parse_error& e)
    {
        const auto& source = e.source();
        const auto& begin = source.begin;
        const auto& end = source.end;

        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(
            DEFAULT_TOML_EXCEPTION_MSG L"Begin: line {}, column {}\nEnd: line {}, column {}", Utils::Widen(e.what()),
            aFile, begin.line, begin.column, end.line, end.column);
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
        auto logLevel = spdlog::level::to_string_view(m_logLevel).data();
        auto flushOn = spdlog::level::to_string_view(m_flushOn).data();

        toml::table config{
            {{"console", m_devConsole}, {"logging", toml::table{{{"level", logLevel}, {"flush_on", flushOn}}}}}};

        std::ofstream file(aFile, std::ios::out);
        file.exceptions(std::ostream::badbit | std::ostream::failbit);

        file << config;
    }
    catch (const toml::parse_error& e)
    {
        const auto& source = e.source();
        const auto& begin = source.begin;
        const auto& end = source.end;

        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(
            DEFAULT_TOML_EXCEPTION_MSG L"Begin: line {}, column {}\nEnd: line {}, column {}", Utils::Widen(e.what()),
            aFile, begin.line, begin.column, end.line, end.column);
    }
    catch (const std::exception& e)
    {
        SHOW_MESSAGE_BOX_FILE_LINE(MB_ICONWARNING | MB_OK, DEFAULT_TOML_EXCEPTION_MSG, Utils::Widen(e.what()), aFile);
    }
}
