#pragma once

#include <RED4ext/RED4define.hpp>
#include <RED4ext/REDreverse/CStackFrame.hpp>
#include <RED4ext/REDreverse/RTTI/CClass.hpp>

namespace RED4ext::REDreverse
{
    struct CBaseFunction
    {
        virtual void sub_0() = 0;
        virtual ~CBaseFunction() = 0;

        virtual void sub_10() = 0;
        virtual uint32_t GetRegistrationIndex() = 0;
        virtual void sub_20() = 0;

        template<typename R = void, typename T>
        auto Call(uintptr_t aScriptable, RED4ext::REDreverse::CStackFrame& aStackFrame, T& aOut, int64_t a4)
        {
            using Call_t = R (*)(uintptr_t, RED4ext::REDreverse::CStackFrame&, T&, int64_t);

            auto func = reinterpret_cast<Call_t>(GetAddress());
            return func(aScriptable, aStackFrame, aOut, a4);
        }

        uint64_t nameHash;
        uint64_t nameHash2;
        int64_t unk18;
        int64_t unk20;
        int64_t unk28;
        int32_t unk30;
        int32_t unk34;
        int64_t* unk38;
        int32_t unk40;
        int32_t unk44;
        int32_t unk48;
        int32_t unk4C;
        int64_t unk50;
        int32_t unk58;
        int32_t unk5C;
        int64_t unk60;
        int64_t unk68;
        int64_t unk70;
        int32_t flags;
        int32_t unk7C;

    private:
        uintptr_t GetAddress();
    };

    RED4EXT_ASSERT_SIZE(CBaseFunction, 0x80);

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
