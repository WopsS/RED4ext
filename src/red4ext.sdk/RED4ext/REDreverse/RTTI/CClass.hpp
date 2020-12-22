#pragma once

#include <RED4ext/REDreverse/RTTI/CRTTIBaseType.hpp>

namespace RED4ext::REDreverse
{
    struct CClassFunction;

    struct CClass : CRTTIBaseType
    {
        struct Functions
        {
            CClassFunction** arr;
            uint32_t capacity;
            uint32_t size;
        };

        struct CProperty
        {
            CRTTIBaseType* type;
            uint64_t name;
            CClass* parent;
            CRTTIBaseType* unk18;
        };

        struct Properties
        {
            CProperty** arr;
            uint32_t capacity;
            uint32_t size;
        };

        CClassFunction* GetFunction(uint64_t aName);

        CRTTIBaseType* parent;
        uint64_t nameHash;
        uint64_t unk20;
        Properties properties;
        Properties properties2;
        Functions functions;
    };

    RED4EXT_ASSERT_SIZE(CClass, 0x58);
    RED4EXT_ASSERT_OFFSET(CClass, parent, 0x10);
    RED4EXT_ASSERT_OFFSET(CClass, properties, 0x28);
    RED4EXT_ASSERT_OFFSET(CClass, functions, 0x48);
}
