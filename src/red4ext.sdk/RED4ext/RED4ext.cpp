#include <algorithm>
#include <windows.h>
#include <DbgHelp.h>
#include <sstream>
#include <vector>
#include <RED4ext/RED4ext.hpp>

namespace RED4ext
{
    struct text_segment
    {
        static uintptr_t get_start_address();
        static uintptr_t get_end_address();
        static text_segment& get();

        uintptr_t start{0};
        uintptr_t end{0};

        text_segment()
        {
            auto* pImage = GetModuleHandleA(nullptr);
            IMAGE_NT_HEADERS* pHeader = ImageNtHeader(pImage);
            auto* pSectionHeaders = reinterpret_cast<IMAGE_SECTION_HEADER*>(pHeader + 1);

            auto base_address = reinterpret_cast<uintptr_t>(pImage);

            for (auto count = 0u; count < pHeader->FileHeader.NumberOfSections; ++count)
            {
                if (memcmp(pSectionHeaders->Name, ".text", 5) == 0)
                {
                    start = base_address + pSectionHeaders->VirtualAddress;
                    end = start + pSectionHeaders->Misc.VirtualSize;

                    return;
                }

                ++pSectionHeaders;
            }
        }
    };

    class pattern
    {
    public:
        pattern() = default;
        pattern(std::vector<uint8_t> pattern);
        bool empty() const;
        size_t size() const;
        std::vector<uintptr_t> find(uint8_t wildcard, uint8_t* start = 0, uint8_t* end = 0) const;

    private:
        std::vector<uint8_t> m_pattern;
    };

    text_segment& text_segment::get()
    {
        static text_segment s_instance;
        return s_instance;
    }


    uintptr_t text_segment::get_start_address()
    {
        return get().start;
    }

    uintptr_t text_segment::get_end_address()
    {
        return get().end;
    }

    pattern::pattern(std::vector<uint8_t> pattern)
        : m_pattern(std::move(pattern))
    {
    }

    bool pattern::empty() const
    {
        return m_pattern.empty();
    }

    size_t pattern::size() const
    {
        return m_pattern.size();
    }

    bool CompareByteArray(uint8_t* Data, const std::vector<uint8_t>& aSignature, uint8_t aWildcard)
    {
        uint8_t* pData = Data;

        for (auto i : aSignature)
        {
            const auto current = *pData;
            pData++;

            if (i == 0xCC)
            {
                continue;
            }

            if (current != i)
            {
                return false;
            }
        }

        return true;
    }

    uint8_t* FindSignature(uint8_t* apStart, uint8_t* apEnd, uint8_t aWildcard, std::vector<uint8_t> aSignature) noexcept
    {
        const uint8_t first = aSignature[0];
        const uint8_t* pEnd = apEnd - aSignature.size();

        for (; apStart < pEnd; ++apStart)
        {
            if (*apStart != first)
            {
                continue;
            }
            if (CompareByteArray(apStart, aSignature, aWildcard))
            {
                return apStart;
            }
        }

        return nullptr;
    }

    std::vector<uintptr_t> pattern::find(uint8_t wildcard, uint8_t* start, uint8_t* end) const
    {
        if (start == 0)
        {
            start = reinterpret_cast<uint8_t*>(text_segment::get_start_address());
        }

        if (end == 0)
        {
            end = reinterpret_cast<uint8_t*>(text_segment::get_end_address());
        }

        std::vector<uintptr_t> offsets;

        while (true)
        {
            auto offset = FindSignature(start, end, wildcard, m_pattern);

            if (offset == nullptr)
            {
                break;
            }

            offsets.emplace_back(reinterpret_cast<uintptr_t>(offset));
            start = offset + m_pattern.size();
        }

        return offsets;
    }

    uintptr_t FindPattern(std::vector<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex,
                                          uint8_t aWildcard)
    {
        pattern pat(aPattern);

        auto addresses = pat.find(aWildcard);
        if (addresses.size() != aExpectedMatches)
        {
            std::ostringstream oss;
            oss << "Pattern fail ";
            for (auto& c : aPattern)
                oss << std::hex << (uint32_t)c << " ";
            oss << " found : " << addresses.size() << " expected : " << aExpectedMatches
                << " wc: " << (uint32_t)aWildcard;

            auto str = oss.str();

            MessageBoxA(0, str.c_str(), "pattern", 0);

            return 0;
        }

        return addresses.at(aIndex);
    }

    uintptr_t GetPatternAddress(const uint8_t* aPattern, size_t aSize, size_t aExpectedMatches, size_t aIndex,
                                uint8_t aWildcard)
    {
        std::vector<uint8_t> pattern(aPattern, aPattern + aSize);
        return FindPattern(pattern, aExpectedMatches, aIndex, aWildcard);
    }
}
