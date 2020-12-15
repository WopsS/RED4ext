#pragma once

namespace REDext::Playground
{
    template<typename T>
    class REDptr
    {
    public:
        REDptr(uintptr_t aAddress)
            : m_address(reinterpret_cast<T>(reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + aAddress))
        {
        }

        T operator*()
        {
            return m_address;
        }

    private:

        T m_address;
    };
}
