#pragma once

template<typename T>
class REDhook
{
public:
    REDhook(std::initializer_list<uint8_t> aPattern, T aDetourAddress, size_t aExpectedMatches, size_t aIndex = 0,
            uint8_t aWildcard = 0xCC)
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

        auto targetAddress = addresses.at(aIndex);
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
