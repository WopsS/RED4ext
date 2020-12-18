#pragma once

#include <cstdint>
#include <initializer_list>

#include <Windows.h>
#include <RED4ext/RED4ext.hpp>

namespace RED4ext
{
    template<typename T>
    class REDfunc
    {
    public:
        REDfunc(uintptr_t aAddress)
            : m_address(reinterpret_cast<T>(aAddress + reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr))))
        {
        }

        REDfunc(std::initializer_list<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex = 0,
                uint8_t aWildcard = 0xCC)
        {
            auto address =
              RED4ext::GetPatternAddress(aPattern.begin(), aPattern.size(), aExpectedMatches, aIndex, aWildcard);
            m_address = reinterpret_cast<T>(address);
        }

        ~REDfunc() = default;

        operator T() const
        {
            return m_address;
        }

    private:
        T m_address;
    };
}
