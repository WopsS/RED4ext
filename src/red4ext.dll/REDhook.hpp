#pragma once

#include "Patterns.hpp"

template<typename T = void (*)()>
class REDhook
{
public:
    REDhook() = default;

    REDhook(uintptr_t aTargetAddress, uintptr_t aDetourAddress)
    {
    }

    REDhook(void* aTargetAddress, void* aDetourAddress)
    {
    }

    REDhook(uintptr_t aTargetAddress, T aDetourAddress)
    {
    }

    REDhook(std::initializer_list<uint8_t> aPattern, T aDetourAddress, size_t aExpectedMatches, size_t aIndex = 0,
            uint8_t aWildcard = 0xCC, bool aIsRequired = true)
    {
    }

    REDhook(REDhook&) = delete;
    REDhook& operator=(const REDhook&) = delete;

    operator T() const
    {
        return reinterpret_cast<T>(nullptr);
    }
};
