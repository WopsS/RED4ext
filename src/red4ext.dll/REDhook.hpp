#pragma once

#include "Patterns.hpp"

template<typename T = void (*)()>
class REDhook : public renhook::inline_hook<T>
{
public:
    REDhook() = default;

    REDhook(uintptr_t aTargetAddress, uintptr_t aDetourAddress)
        : renhook::inline_hook<T>(aTargetAddress, aDetourAddress)
    {
    }

    REDhook(void* aTargetAddress, void* aDetourAddress)
        : REDhook(reinterpret_cast<uintptr_t>(aTargetAddress), reinterpret_cast<uintptr_t>(aDetourAddress))
    {
    }

    REDhook(uintptr_t aTargetAddress, T aDetourAddress)
        : REDhook(aTargetAddress, reinterpret_cast<uintptr_t>(aDetourAddress))
    {
    }

    REDhook(std::initializer_list<uint8_t> aPattern, T aDetourAddress, size_t aExpectedMatches, size_t aIndex = 0,
            uint8_t aWildcard = 0xCC, bool aIsRequired = true)
        : REDhook(Patterns::Get()->Find(aPattern, aExpectedMatches, aIndex, aWildcard, aIsRequired), aDetourAddress)
    {
    }

    REDhook(REDhook&) = delete;
    REDhook& operator=(const REDhook&) = delete;
};
