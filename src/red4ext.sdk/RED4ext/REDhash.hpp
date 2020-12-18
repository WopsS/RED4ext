#pragma once

#include <cstdint>
#include <string_view>

namespace RED4ext
{
    constexpr uint64_t FNV1a(std::string_view aText)
    {
        constexpr uint64_t basis = 0xCBF29CE484222325;
        constexpr uint64_t prime = 0x100000001b3;

        uint64_t hash = basis;
        for (auto c : aText)
        {
            hash ^= c;
            hash *= prime;
        }

        return hash;
    }
}
