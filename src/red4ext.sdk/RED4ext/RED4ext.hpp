#pragma once

#include <cstdint>

#include <RED4ext/RED4define.hpp>

namespace RED4ext
{
    namespace Log
    {
        RED4EXT_IMPORT void Trace(const char* aName, const char* aMessage);
        RED4EXT_IMPORT void Debug(const char* aName, const char* aMessage);
        RED4EXT_IMPORT void Info(const char* aName, const char* aMessage);
        RED4EXT_IMPORT void Warn(const char* aName, const char* aMessage);
        RED4EXT_IMPORT void Error(const char* aName, const char* aMessage);
        RED4EXT_IMPORT void Critical(const char* aName, const char* aMessage);
    }

    RED4EXT_IMPORT uintptr_t GetPatternAddress(const uint8_t* aPattern, size_t aLength, size_t aExpectedMatches,
                                               size_t aIndex = 0, uint8_t aWildcard = 0xCC);
}
