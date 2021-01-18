#include "stdafx.hpp"
#include "Utils.hpp"

uintptr_t RED4ext::Utils::FindPattern(std::vector<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex,
                                      uint8_t aWildcard)
{
    renhook::pattern pattern(aPattern);

    auto addresses = pattern.find(aWildcard);
    if (addresses.size() != aExpectedMatches)
    {
        std::wstring message;
        std::wostringstream stream;

        stream << L"The pattern { ";

        for (auto it = aPattern.begin(); it != aPattern.end(); ++it)
        {
            if (it != aPattern.begin())
            {
                stream << L", ";
            }

            stream << L"0x" << std::uppercase << std::setfill(L'0') << std::setw(2) << std::hex
                   << static_cast<uint32_t>(*it);
        }

        stream << L" } ";

        if (addresses.size() == 0)
        {
            stream << L"could not be found.";
        }
        else
        {
            stream << L"returned " << addresses.size() << L" match(es) but " << aExpectedMatches
                   << L" match(es) were expected.";
        }

        stream << L"\n\nThe process will be terminated.";
        message = stream.str();

        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_OK | MB_ICONERROR);
        ExitProcess(1);
    }

    return addresses.at(aIndex);
}

uintptr_t RED4ext::Utils::FindPattern(std::initializer_list<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex,
                                      uint8_t aWildcard)
{
    return FindPattern(std::vector(aPattern), aExpectedMatches, aIndex, aWildcard);
}
