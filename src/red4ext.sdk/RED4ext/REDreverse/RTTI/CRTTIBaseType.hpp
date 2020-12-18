#pragma once

#include <cstdint>

#include <RED4ext/RED4define.hpp>

namespace RED4ext::REDreverse
{
    enum class RTTIType : uint8_t
    {
        Name,
        Fundamental,
        Class,
        Array,
        Simple,
        Enum,
        StaticArray,
        NativeArray,
        Pointer,
        Handle,
        WeakHandle,
        ResourceReference,
        ResourceAsyncReference,
        BitField,
        LegacySingleChannelCurve,
        ScriptReference
    };

    struct CRTTIBaseType
    {
        virtual ~CRTTIBaseType() = 0;
        virtual void GetName(uint64_t* aOut) = 0;
        virtual void sub_10() = 0;
        virtual void sub_18() = 0;
        virtual RTTIType GetType() = 0;

        int64_t unk8;
    };

    RED4EXT_ASSERT_SIZE(CRTTIBaseType, 0x10);
}
