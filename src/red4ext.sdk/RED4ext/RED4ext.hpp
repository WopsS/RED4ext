#pragma once

#include <cstdint>
#include <vector>

namespace RED4ext
{
    uintptr_t FindPattern(std::vector<uint8_t> aPattern, size_t aExpectedMatches = 1, size_t aIndex = 0, uint8_t aWildcard = 0xCC);

    uintptr_t GetPatternAddress(const uint8_t* aPattern, size_t aLength, size_t aExpectedMatches,
                                               size_t aIndex = 0, uint8_t aWildcard = 0xCC);
}
