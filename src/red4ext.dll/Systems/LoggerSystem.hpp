#pragma once

#include "PluginBase.hpp"
#include "Utils.hpp"

class LoggerSystem
{
public:
    LoggerSystem(const Paths& aPaths, const Config& aConfig, const DevConsole& aDevConsole);

    void Shutdown();

    void Trace(std::shared_ptr<PluginBase> aPlugin, std::string_view aText);
    void Trace(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText);

    void Debug(std::shared_ptr<PluginBase> aPlugin, std::string_view aText);
    void Debug(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText);

    void Info(std::shared_ptr<PluginBase> aPlugin, std::string_view aText);
    void Info(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText);

    void Warn(std::shared_ptr<PluginBase> aPlugin, std::string_view aText);
    void Warn(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText);

    void Error(std::shared_ptr<PluginBase> aPlugin, std::string_view aText);
    void Error(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText);

    void Critical(std::shared_ptr<PluginBase> aPlugin, std::string_view aText);
    void Critical(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText);

private:
    template<typename T>
    inline void Log(std::shared_ptr<PluginBase> aPlugin, spdlog::level::level_enum aLevel,
                    std::basic_string_view<T> aText)
    {
        if (!aPlugin /*|| aText.empty()*/)
        {
            return;
        }

        std::shared_ptr<spdlog::logger> logger;

        auto it = m_loggers.find(aPlugin);
        if (it != m_loggers.end())
        {
            logger = it->second;
        }
        else
        {
            const auto logName = aPlugin->GetName();

            const auto& path = aPlugin->GetPath();
            auto fileName = path.stem().wstring();
            std::transform(fileName.begin(), fileName.end(), fileName.begin(),
                           [](wchar_t aC) { return std::tolower(aC); });

            logger = Utils::CreateLogger(logName, fmt::format(L"{}.log", fileName), m_paths, m_config, m_devConsole);
            m_loggers.emplace(aPlugin, logger);
        }

        logger->log(aLevel, aText);
    }

    const Paths& m_paths;
    const Config& m_config;
    const DevConsole& m_devConsole;

    std::unordered_map<std::shared_ptr<PluginBase>, std::shared_ptr<spdlog::logger>> m_loggers;
};
