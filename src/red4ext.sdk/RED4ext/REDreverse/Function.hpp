#pragma once

#include <RED4ext/RED4define.hpp>
#include <RED4ext/REDreverse/Scripting/StackFrame.hpp>
#include <RED4ext/REDreverse/RTTI/CClass.hpp>

namespace RED4ext::REDreverse
{
    struct CBaseFunction
    {
        struct Unk
        {
            struct Param
            {
                CRTTIBaseType* type;
                uint8_t pad8[0x28 - 0x8];
                uint32_t flag;
            };

            Param** arr;
            uint32_t capacity;
            uint32_t size;
        };


        virtual void sub_0() = 0;
        virtual ~CBaseFunction() = 0;

        virtual void sub_10() = 0;
        virtual uint32_t GetRegistrationIndex() = 0;
        virtual void sub_20() = 0;

        bool Call(CScriptableStackFrame* aStack);

        uint64_t nameHash;
        uint64_t nameHash2;
        CRTTIBaseType** returnType;
        int64_t unk20;
        Unk params;
        Unk unk38;
        int32_t unk48;
        int32_t unk4C;
        char* byteCode;
        int32_t unk58;
        int32_t unk5C;
        int64_t unk60;
        int64_t unk68;
        int64_t unk70;
        int32_t flags;
        int32_t unk7C;
    };

    RED4EXT_ASSERT_SIZE(CBaseFunction, 0x80);
    RED4EXT_ASSERT_OFFSET(CBaseFunction::Unk::Param, flag, 0x28);

    struct CGlobalFunction : CBaseFunction
    {
        uint32_t registrationIndex;
    };

    RED4EXT_ASSERT_SIZE(CGlobalFunction, 0x88);
    RED4EXT_ASSERT_OFFSET(CGlobalFunction, registrationIndex, 0x80);

    struct CClassFunction : CBaseFunction
    {
        CClass* parent;
        uint32_t registrationIndex;
    };

    RED4EXT_ASSERT_SIZE(CClassFunction, 0x90);
    RED4EXT_ASSERT_OFFSET(CClassFunction, parent, 0x80);
}
