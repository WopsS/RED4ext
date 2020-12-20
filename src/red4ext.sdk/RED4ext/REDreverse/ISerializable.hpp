#pragma once

#include <RED4ext/RED4define.hpp>

namespace RED4ext::REDreverse
{
    struct ISerializable
    {
        uintptr_t vtbl;
    };

    RED4EXT_ASSERT_SIZE(ISerializable, 0x8);
}
