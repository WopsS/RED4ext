#pragma once

#include "Addresses.hpp"

template<typename T>
class Hook
{
public:
    Hook(T aAddress, T aDetour)
        : m_isAttached(false)
        , m_address(aAddress)
        , m_detour(aDetour)
        , m_hash(0)
    {
    }

    Hook(std::uint32_t aHash, T aDetour)
        : Hook(reinterpret_cast<T>(0), aDetour)
    {
        m_hash = aHash;
    }

    operator T() const
    {
        return m_address;
    }

    uintptr_t GetAddress() const
    {
        if (m_address == 0)
        {
            const auto address = Addresses::Instance();
            m_address = reinterpret_cast<T>(address->Resolve(m_hash));
        }

        return reinterpret_cast<uintptr_t>(m_address);
    }

    int32_t Attach()
    {
        if (m_isAttached)
        {
            return 0;
        }

        if (m_address == 0)
        {
            m_address = reinterpret_cast<T>(GetAddress());
        }

        auto result = DetourAttach(&m_address, m_detour);
        m_isAttached = result == NO_ERROR;

        return result;
    }

    int32_t Detach()
    {
        if (!m_isAttached)
        {
            return 0;
        }

        auto result = DetourDetach(&m_address, m_detour);
        m_isAttached = result == NO_ERROR;

        return result;
    }

private:
    bool m_isAttached;
    mutable T m_address;
    T m_detour;

    uint32_t m_hash;
};
