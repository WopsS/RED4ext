#pragma once

#include <cstdint>

#include <RED4ext/RED4define.hpp>

namespace RED4ext::REDreverse
{
    struct CString
    {
#pragma pack(push, 4)
        union
        {
            char* ptr;
            char cstr[0x14];
        } str;
#pragma pack(pop)

        CString(const char* aText);

        uint32_t length;
        uint64_t capacity;
    };

    RED4EXT_ASSERT_SIZE(CString, 0x20);
    RED4EXT_ASSERT_OFFSET(CString, length, 0x14);
    RED4EXT_ASSERT_OFFSET(CString, capacity, 0x18);
}
