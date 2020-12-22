#pragma once

#include <cstdint>

namespace RED4ext::REDreverse
{
    struct CName
    {
        static const char* ToString(uint64_t aHash);
    };
}
