#include "stdafx.hpp"
#include "LoggerSystem.hpp"

LoggerSystem::LoggerSystem(const Paths& aPaths, const Config& aConfig, const DevConsole& aDevConsole)
    : m_paths(aPaths)
    , m_config(aConfig)
    , m_devConsole(aDevConsole)
{
}

ESystemType LoggerSystem::GetType()
{
    return ESystemType::Logger;
}

void LoggerSystem::Startup()
{
}

void LoggerSystem::Shutdown()
{
    auto count = m_loggers.size();

    spdlog::trace("Flusing {} logger(s)...", count);

    for (auto& [plugin, logger] : m_loggers)
    {
        logger->flush();
    }

    m_loggers.clear();
    spdlog::trace("{} logger(s) flushed", count);
}

void LoggerSystem::Trace(std::shared_ptr<PluginBase> aPlugin, std::string_view aText)
{
    Log(aPlugin, spdlog::level::trace, aText);
}

void LoggerSystem::Trace(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText)
{
    Log(aPlugin, spdlog::level::trace, aText);
}

void LoggerSystem::Debug(std::shared_ptr<PluginBase> aPlugin, std::string_view aText)
{
    Log(aPlugin, spdlog::level::debug, aText);
}

void LoggerSystem::Debug(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText)
{
    Log(aPlugin, spdlog::level::debug, aText);
}

void LoggerSystem::Info(std::shared_ptr<PluginBase> aPlugin, std::string_view aText)
{
    Log(aPlugin, spdlog::level::info, aText);
}

void LoggerSystem::Info(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText)
{
    Log(aPlugin, spdlog::level::info, aText);
}

void LoggerSystem::Warn(std::shared_ptr<PluginBase> aPlugin, std::string_view aText)
{
    Log(aPlugin, spdlog::level::warn, aText);
}

void LoggerSystem::Warn(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText)
{
    Log(aPlugin, spdlog::level::warn, aText);
}

void LoggerSystem::Error(std::shared_ptr<PluginBase> aPlugin, std::string_view aText)
{
    Log(aPlugin, spdlog::level::err, aText);
}

void LoggerSystem::Error(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText)
{
    Log(aPlugin, spdlog::level::err, aText);
}

void LoggerSystem::Critical(std::shared_ptr<PluginBase> aPlugin, std::string_view aText)
{
    Log(aPlugin, spdlog::level::critical, aText);
}

void LoggerSystem::Critical(std::shared_ptr<PluginBase> aPlugin, std::wstring_view aText)
{
    Log(aPlugin, spdlog::level::critical, aText);
}
