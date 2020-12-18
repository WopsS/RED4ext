#pragma once

#include <Utils.hpp>

namespace RED4ext
{
    template<typename T>
    class REDhook
    {
    public:
        REDhook(std::initializer_list<uint8_t> aPattern, T aDetourAddress, size_t aExpectedMatches, size_t aIndex = 0,
                uint8_t aWildcard = 0xCC)
        {
            auto targetAddress = Utils::FindPattern(aPattern, aExpectedMatches, aIndex, aWildcard);
            m_hook = renhook::inline_hook<T>(targetAddress, aDetourAddress);
        }

        operator T() const
        {
            return m_hook;
        }

        void Attach()
        {
            m_hook.attach();
        }

        void Detach()
        {
            m_hook.detach();
        }

    private:
        renhook::inline_hook<T> m_hook;
    };
}
