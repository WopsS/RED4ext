#pragma once

#include <cstdint>
#include <initializer_list>

#include <Windows.h>
#include <RED4ext/RED4ext.hpp>

namespace RED4ext
{
    template<typename T>
    class REDarray
    {
    public:
        REDarray(uintptr_t aAddress)
            : m_address(reinterpret_cast<T*>(aAddress + reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr))))
        {
        }

        REDarray(std::initializer_list<uint8_t> aPattern, size_t aExpectedMatches, size_t aOffset, size_t aIndex = 0,
                 uint8_t aWildcard = 0xCC)
        {
            auto address =
              RED4ext::GetPatternAddress(aPattern.begin(), aPattern.size(), aExpectedMatches, aIndex, aWildcard) +
              aOffset;

            m_address = reinterpret_cast<T*>(address + *reinterpret_cast<int32_t*>(address) + 4);
        }

        ~REDarray() = default;

        T operator[](T aIndex) const
        {
            return m_address[aIndex];
        }

    private:
        T* m_address;
    };
}
