#include <stdafx.hpp>
#include <Exports/Exports.hpp>
#include <Utils.hpp>

namespace RED4ext
{
    RED4EXT_EXPORT uintptr_t GetPatternAddress(const uint8_t* aPattern, size_t aSize, size_t aExpectedMatches,
                                               size_t aIndex, uint8_t aWildcard)
    {
        std::vector<uint8_t> pattern(aPattern, aPattern + aSize);
        return RED4ext::Utils::FindPattern(pattern, aExpectedMatches, aIndex, aWildcard);
    }
}
