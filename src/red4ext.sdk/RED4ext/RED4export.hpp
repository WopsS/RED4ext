#pragma once

#ifndef RED4EXT_EXTERN_C
#define RED4EXT_EXTERN_C extern "C"
#endif

#ifndef RED4EXT_EXPORT
#define RED4EXT_EXPORT RED4EXT_EXTERN_C __declspec(dllexport)
#endif
