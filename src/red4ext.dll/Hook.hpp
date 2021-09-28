#pragma once

template<typename T>
class Hook
{
public:
    Hook(uintptr_t aOffset, T aDetour)
        : m_isAttached(false)
        , m_address(reinterpret_cast<T>(reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + aOffset))
        , m_detour(aDetour)
    {
    }

    operator T() const
    {
        return m_address;
    }

    int32_t Attach()
    {
        if (m_isAttached)
        {
            return 0;
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
    T m_address;
    T m_detour;
};
