#include "stdafx.hpp"
#include "Patterns.hpp"

Patterns* Patterns::Get()
{
    static Patterns patterns;
    return &patterns;
}

uintptr_t Patterns::Find(const uint8_t* aPattern, size_t aPatternSize, size_t aExpectedMatches, size_t aIndex,
                         uint8_t aWildcard, bool aIsRequired)
{
    if (!aPattern || !aPatternSize)
    {
        return {};
    }

    std::vector<uint8_t*> addresses;
    auto end = aPattern + aPatternSize;

    //auto codeStart = reinterpret_cast<uint8_t*>(renhook::executable::get_code_base_address());
    //auto codeEnd = reinterpret_cast<uint8_t*>(renhook::executable::get_code_end_address());

    uint8_t* codeStart = nullptr;
    uint8_t* codeEnd = nullptr;

    while (true)
    {
        auto address =
            std::search(codeStart, codeEnd, aPattern, end, [aWildcard](uint8_t aMemoryValue, uint8_t aPatternValue) {
                return aMemoryValue == aPatternValue || aPatternValue == aWildcard;
            });

        // Did it reach the end?
        if (address >= codeEnd)
        {
            break;
        }

        addresses.emplace_back(address);
        codeStart = address + aPatternSize;
    }

    if (addresses.size() == aExpectedMatches)
    {
        auto address = addresses.at(aIndex);
        return reinterpret_cast<uintptr_t>(address);
    }
    else if (aIsRequired)
    {
        fmt::wmemory_buffer out;
        fmt::format_to(out, L"The pattern {{ 0x{:02X} }} ", fmt::join(aPattern, end, L", 0x"));

        if (addresses.size() == 0)
        {
            fmt::format_to(out, L"could not be found.");
        }
        else
        {
            fmt::format_to(out, L"returned {} match(es) but {} match(es) were expected.", addresses.size(),
                           aExpectedMatches);
        }

        fmt::format_to(out,
                       L"\n\nThis might be because the game's version is not supported. Try to use a RED4ext version "
                       L"that is compatible with the game's version.\n\n"
                       L"The process will be terminated.");

        auto message = fmt::to_string(out);
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONERROR | MB_OK);
        ExitProcess(1);
    }

    return 0;
}

uintptr_t Patterns::Find(std::initializer_list<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex,
                         uint8_t aWildcard, bool aIsRequired)
{
    return Find(aPattern.begin(), aPattern.size(), aExpectedMatches, aIndex, aWildcard, aIsRequired);
}
