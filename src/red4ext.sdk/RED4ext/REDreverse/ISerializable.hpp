#pragma once

#include "RTTI/CClass.hpp"
#include <RED4ext/RED4define.hpp>

namespace RED4ext::REDreverse
{
    struct ISerializable
    {
        virtual CClass* GetParentClass();
        virtual CClass* GetClass();
    };

    RED4EXT_ASSERT_SIZE(ISerializable, 0x8);
}
