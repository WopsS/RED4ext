#include <RED4ext/REDreverse/RTTI/CClass.hpp>

#include <RED4ext/REDfunc.hpp>

namespace
{
    using CClass_GetFunction_t = RED4ext::REDreverse::CClassFunction* (*)(RED4ext::REDreverse::CRTTIBaseType* aClass,
                                                                          uint64_t aName);
    
}

RED4ext::REDreverse::CClassFunction* RED4ext::REDreverse::CClass::GetFunction(uint64_t aName)
{
    static RED4ext::REDfunc<CClass_GetFunction_t> CClass_GetFunction(
      { 0x4C, 0x8B, 0xC9, 0x48, 0x85, 0xC9, 0x74, 0x5E, 0x49, 0x8B, 0x41, 0x48 }, 1);

    return CClass_GetFunction(this, aName);
}
