#include <stdafx.hpp>
#include <Exports/Exports.hpp>

namespace
{
    std::string Format(const char* aName, const char* aMessage)
    {
        if (aName && std::strlen(aName))
        {
            return fmt::format("[{}] {}", aName, aMessage);
        }

        return aMessage;
    }
}

namespace RED4ext::Log
{
    RED4EXT_EXPORT void Trace(const char* aName, const char* aMessage)
    {
        spdlog::trace(Format(aName, aMessage));
    }

    RED4EXT_EXPORT void Debug(const char* aName, const char* aMessage)
    {
        spdlog::debug(Format(aName, aMessage));
    }

    RED4EXT_EXPORT void Info(const char* aName, const char* aMessage)
    {
        spdlog::info(Format(aName, aMessage));
    }

    RED4EXT_EXPORT void Warn(const char* aName, const char* aMessage)
    {
        spdlog::warn(Format(aName, aMessage));
    }

    RED4EXT_EXPORT void Error(const char* aName, const char* aMessage)
    {
        spdlog::error(Format(aName, aMessage));
    }

    RED4EXT_EXPORT void Critical(const char* aName, const char* aMessage)
    {
        spdlog::critical(Format(aName, aMessage));
    }
}
