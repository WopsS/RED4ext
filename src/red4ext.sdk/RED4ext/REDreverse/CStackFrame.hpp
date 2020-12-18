#pragma once

#include <cstdint>
#include <RED4ext/RED4define.hpp>

namespace RED4ext::REDreverse
{
    struct CStackFrame
    {
        CStackFrame();
        ~CStackFrame() = default;

        char* byteCode;
        int64_t unk8;
        int64_t unk10;
        int64_t unk18;
        int64_t unk20;
        int64_t unk28;
        int64_t unk30;
        int64_t unk38;
        int64_t scriptable;
        int64_t unk48;
        int16_t unk50;
        int64_t unk58;
        int8_t unk60;
    };

    RED4EXT_ASSERT_SIZE(CStackFrame, 0x68);
}
