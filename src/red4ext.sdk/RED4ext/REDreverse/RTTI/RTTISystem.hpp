#pragma once

#include <cstdint>
#include <type_traits>

#include <RED4ext/REDreverse/Function.hpp>
#include <RED4ext/REDreverse/RTTI/CClass.hpp>
#include <RED4ext/REDreverse/RTTI/CRTTIBaseType.hpp>

namespace RED4ext::REDreverse
{
    struct IRTTISystem
    {
        virtual CRTTIBaseType* GetType(uint64_t aNameHash) = 0;
        virtual void sub_8() = 0;
        virtual CClass* GetClass(uint64_t aNameHash) = 0;
        virtual CRTTIBaseType* GetEnum(uint64_t aNameHash) = 0;
        virtual CRTTIBaseType* GetBitField(uint64_t aNameHash) = 0;
        virtual void sub_28() = 0;
        virtual CGlobalFunction* GetGloblaFunction(uint64_t aNameHash) = 0;
        virtual void sub_38() = 0;
        virtual void sub_40() = 0;
        virtual void sub_48() = 0;
        virtual void sub_50() = 0;
        virtual void sub_58() = 0;
        virtual void sub_60() = 0;
        virtual void sub_68() = 0;
        virtual void sub_70() = 0;
        virtual void sub_78() = 0;
        virtual int64_t RegisterType(CRTTIBaseType* aType, uint32_t a2) = 0;
        virtual void sub_88() = 0;
        virtual void sub_90() = 0;
        virtual void RegisterFunction() = 0;
        virtual void sub_A0() = 0;
        virtual void sub_A8() = 0;
        virtual void sub_B0() = 0;
        virtual void sub_B8() = 0;
        virtual void sub_C0() = 0;
        virtual void sub_C8() = 0;
        virtual void sub_D0() = 0;
        virtual void sub_D8() = 0;
        virtual void sub_E0() = 0;
        virtual void sub_E8() = 0;
        virtual void sub_F0() = 0;
        virtual void sub_F8() = 0;
        virtual void sub_100() = 0;

        virtual ~IRTTISystem() = 0;

        template<typename T>
        std::enable_if_t<std::is_pointer_v<T> &&
                           std::is_base_of_v<CRTTIBaseType, std::remove_cv_t<std::remove_pointer_t<T>>> &&
                           !std::is_same_v<std::remove_cv_t<std::remove_pointer_t<T>>, CRTTIBaseType>,
                         T>
        GetType(uint64_t aNameHash)
        {
            return static_cast<T>(GetType(aNameHash));
        }
    };

    RED4EXT_ASSERT_SIZE(IRTTISystem, 0x8);

    struct CRTTISystem : IRTTISystem
    {
        static CRTTISystem* Get();
    };

    RED4EXT_ASSERT_SIZE(CRTTISystem, 0x8);
}
