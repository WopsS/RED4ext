#pragma once

#ifndef REDEXT_EXTERN_C
#define REDEXT_EXTERN_C extern "C"
#endif

#ifndef REDEXT_EXPORT
#define REDEXT_EXPORT REDEXT_EXTERN_C __declspec(dllexport)
#endif
