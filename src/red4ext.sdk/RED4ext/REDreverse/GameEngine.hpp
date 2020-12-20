#pragma once

#include <cstdint>

#include <RED4ext/RED4define.hpp>
#include <RED4ext/REDreverse/RTTI/CRTTIBaseType.hpp>
#include <RED4ext/REDreverse/Scripting/IScriptable.hpp>

namespace RED4ext::REDreverse
{
    struct BaseGameEngine
    {
        virtual void sub_0() = 0;
    };

    RED4EXT_ASSERT_SIZE(BaseGameEngine, 0x8);

    struct CBaseEngine : BaseGameEngine
    {
    };

    RED4EXT_ASSERT_SIZE(CBaseEngine, 0x8);

    struct CGameEngine : CBaseEngine
    {
        struct CGameFramework
        {
            struct Unk
            {
                virtual ~Unk() = 0;
                virtual Scripting::IScriptable* GetTypeInstance(const CRTTIBaseType* aClass) = 0;
            };

            RED4EXT_ASSERT_SIZE(Unk, 0x8);

            int8_t unk0[0x10];
            Unk* unk10;
        };

        RED4EXT_ASSERT_SIZE(CGameFramework, 0x18);
        RED4EXT_ASSERT_OFFSET(CGameFramework, unk10, 0x10);

        static CGameEngine* Get();

        int8_t unk0[0x258];
        CGameFramework* framework;
    };

    RED4EXT_ASSERT_SIZE(CGameEngine, 0x268);
    RED4EXT_ASSERT_OFFSET(CGameEngine, framework, 0x260);
}
