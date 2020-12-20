#pragma once

#include <cstdint>

#include <RED4ext/RED4define.hpp>
#include <RED4ext/REDreverse/RTTI/CRTTIBaseType.hpp>
#include <RED4ext/REDreverse/Scripting/IScriptable.hpp>

namespace RED4ext::REDreverse
{
    struct CBaseStackFrame
    {
        virtual void sub_0() = 0;
        virtual uint64_t GetResultAddress() = 0;
        virtual int64_t sub_10() = 0;
        virtual void sub_18(int64_t a2) = 0;

        int64_t unk8;
        int64_t unk10;
        Scripting::IScriptable* scriptable18;
        Scripting::IScriptable* scriptable20;
        int64_t unk28;
    };

    RED4EXT_ASSERT_SIZE(CBaseStackFrame, 0x30);

    struct CScriptableStackFrame : CBaseStackFrame
    {
        struct CStackType
        {
            CStackType()
                : type(nullptr)
                , value(nullptr)
            {
            }

            CRTTIBaseType* type;
            void* value;
        };

        static CScriptableStackFrame* Construct(CScriptableStackFrame* aThis, Scripting::IScriptable* aScriptable,
                                                CScriptableStackFrame::CStackType* aArgs, uint32_t aArgsCount,
                                                CScriptableStackFrame::CStackType* aResult, int64_t a6);

        CStackType* args;
        int32_t argCount;
        CStackType* result;
    };

    RED4EXT_ASSERT_SIZE(CScriptableStackFrame, 0x48);
    RED4EXT_ASSERT_OFFSET(CScriptableStackFrame, args, 0x30);
    RED4EXT_ASSERT_OFFSET(CScriptableStackFrame, argCount, 0x38);
    RED4EXT_ASSERT_OFFSET(CScriptableStackFrame, result, 0x40);
}
