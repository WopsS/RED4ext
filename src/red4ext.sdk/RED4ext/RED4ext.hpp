#pragma once

#include <cstdint>

namespace RED4ext
{
    uintptr_t GetPatternAddress(const uint8_t* aPattern, size_t aLength, size_t aExpectedMatches,
                                               size_t aIndex = 0, uint8_t aWildcard = 0xCC);
}
