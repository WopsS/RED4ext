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

        CString();
        CString(const char* aText);

        CString* Copy(CString* apRhs);
        void Destroy();

        const char* ToString() const
        {
            if (length >= 0x40000000u)
                return str.ptr;
            return str.cstr;
        }

        uint32_t length;
        uint64_t capacity;
    };

    RED4EXT_ASSERT_SIZE(CString, 0x20);
    RED4EXT_ASSERT_OFFSET(CString, length, 0x14);
    RED4EXT_ASSERT_OFFSET(CString, capacity, 0x18);
}
