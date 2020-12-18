#pragma once

#include <RED4ext/REDreverse/RTTI/CRTTIBaseType.hpp>

namespace RED4ext::REDreverse
{
    struct CClassFunction;

    struct CClass : CRTTIBaseType
    {
        CClassFunction* GetFunction(uint64_t aName);

        CClass* parent;
    };

    RED4EXT_ASSERT_SIZE(CClass, 0x18);
    RED4EXT_ASSERT_OFFSET(CClass, parent, 0x10);
}
