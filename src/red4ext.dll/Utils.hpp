#pragma once

namespace RED4ext::Utils
{
    uintptr_t FindPattern(std::vector<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex = 0,
                          uint8_t aWildcard = 0xCC);

    uintptr_t FindPattern(std::initializer_list<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex = 0,
                          uint8_t aWildcard = 0xCC);
}
