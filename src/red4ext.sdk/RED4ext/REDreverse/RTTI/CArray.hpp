#pragma once

#include <RED4ext/REDreverse/RTTI/CRTTIBaseType.hpp>

namespace RED4ext::REDreverse
{
    struct CArray : CRTTIBaseType
    {
        CRTTIBaseType* heldType;
        uint64_t nameHash;
        CRTTIBaseType** parent;
        CRTTIBaseType* unk20;
        CRTTIBaseType* unk28;
        CRTTIBaseType* unk30;
    };

    RED4EXT_ASSERT_SIZE(CArray, 0x40);
    RED4EXT_ASSERT_OFFSET(CArray, parent, 0x20);
}
