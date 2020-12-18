#pragma once

#include <cstddef>

#ifndef RED4EXT_ASSERT_SIZE
#define RED4EXT_ASSERT_SIZE(cls, size) \
    static_assert(sizeof(cls) == size, #cls " size does not match the expected size");
#endif

#ifndef RED4EXT_ASSERT_OFFSET
#define RED4EXT_ASSERT_OFFSET(cls, mbr, offset) \
    static_assert(offsetof(cls, mbr) == offset, #cls "::" #mbr " is misaligned");
#endif

#ifndef RED4EXT_IMPORT
#define RED4EXT_IMPORT __declspec(dllimport)
#endif

#ifndef RED4EXT_EXTERN_C
#define RED4EXT_EXTERN_C extern "C"
#endif

#ifndef RED4EXT_EXPORT
#define RED4EXT_EXPORT RED4EXT_EXTERN_C __declspec(dllexport)
#endif
