#pragma once

namespace REDext::Playground
{
    template<typename T>
    class REDfunc
    {
    public:
        REDfunc(uintptr_t aAddress)
            : m_address(reinterpret_cast<T>(reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + aAddress))
        {
        }

        operator T() const
        {
            return m_address;
        }

    private:
        T m_address;
    };
}
