#pragma once

#include "Patterns.hpp"

template<typename T = void (*)()>
class REDhook
{
public:
    REDhook()
        : m_attached(false)
        , m_real_addresss(0)
        , m_detour_address(0)
    {
    }

    REDhook(T aTargetAddress, T aDetourAddress)
        : m_attached(false)
        , m_real_addresss(aTargetAddress)
        , m_detour_address(aDetourAddress)
    {
    }

    REDhook(uintptr_t aTargetAddress, uintptr_t aDetourAddress)
        : REDhook(reinterpret_cast<T>(aTargetAddress), reinterpret_cast<T>(aDetourAddress))
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
        return m_real_addresss;
    }

    int32_t Attach()
    {
        return Attach(reinterpret_cast<void**>(&m_real_addresss));
    }

    int32_t Attach(void** aTargetAddress)
    {
        auto result = DetourAttach(aTargetAddress, reinterpret_cast<void*>(m_detour_address));
        m_attached = true;

        return result;
    }

    int32_t Detach()
    {
        return Detach(reinterpret_cast<void**>(&m_real_addresss));
    }

    int32_t Detach(void** aTargetAddress)
    {
        auto result = DetourDetach(aTargetAddress, reinterpret_cast<void*>(m_detour_address));
        m_attached = false;

        return result;
    }

    bool IsAttached() const
    {
        return m_attached;
    }

private:
    bool m_attached;
    T m_real_addresss;
    T m_detour_address;
};
