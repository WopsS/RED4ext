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
        if (addresses.size() == aExpectedMatches)
        {
            fmt::wmemory_buffer out;
            fmt::format_to(out, L"The pattern {{ 0x{:02X} }} ", fmt::join(aPattern, L", 0x"));

            if (addresses.size() == 0)
            {
                fmt::format_to(out, L"could not be found.");
            }
            else
            {
                fmt::format_to(out, L"returned {} match(es) but {} match(es) were expected.", addresses.size(),
                               aExpectedMatches);
            }

            fmt::format_to(out, L"\n\nThis might be because the game's version is not supported. Try to use a version "
                                L"that is compatible with the game's version.\n\n"
                                L"The process will be terminated.");

            auto message = fmt::to_string(out);
            MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONERROR | MB_OK);
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
