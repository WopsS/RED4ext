#include <RED4ext/REDreverse/CString.hpp>

#include <RED4ext/REDfunc.hpp>

namespace
{
    using namespace RED4ext::REDreverse;
    using CString_ctor_t = CString* (*)(CString* aThis, const char*);
    using CString_dtor_t = CString* (*)(CString* aThis);
    using CString_copy_t = CString* (*)(CString* aThis, CString* apRhs);

}

CString::CString()
    : CString("")
{
}

CString::CString(const char* aText)
{
    static RED4ext::REDfunc<CString_ctor_t> CString_ctor(
      { 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x33, 0xC0, 0xC6, 0x01, 0x00 }, 4, 2);

    CString_ctor(this, aText);
}

CString* CString::Copy(CString* apRhs)
{
    static uint8_t* CopyCaller = reinterpret_cast<uint8_t*>(FindPattern(
    { 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B, 0xCA, 0x49, 0x8B, 0xD8, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC, 0x48,
      0x8B, 0xD0, 0x48, 0x8B, 0xCB, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC, 0xB0, 0x01, 0x48, 0x83, 0xC4, 0x20, 0x5B, 0xC3 }, 1));
    
    static CString_copy_t RealStringCopy =
      reinterpret_cast<CString_copy_t>(&CopyCaller[28] + *reinterpret_cast<int32_t*>(&CopyCaller[24]));

    return RealStringCopy(this, apRhs);
}

void CString::Destroy()
{
    static REDfunc<CString_dtor_t> CString_dtor(
      { 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B, 0xD9, 0x8B, 0x49, 0x14, 0x8B, 0xC1, 0xC1, 0xE8 }, 1);

    CString_dtor(this);
}
