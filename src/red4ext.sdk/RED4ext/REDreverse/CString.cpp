#include <RED4ext/REDreverse/CString.hpp>

#include <RED4ext/REDfunc.hpp>

namespace
{
    using namespace RED4ext::REDreverse;
    using CString_ctor_t = CString* (*)(CString* aThis, const char*);

}

RED4ext::REDreverse::CString::CString()
    : CString("")
{
}

RED4ext::REDreverse::CString::CString(const char* aText)
{
    static RED4ext::REDfunc<CString_ctor_t> CString_ctor(
      { 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x33, 0xC0, 0xC6, 0x01, 0x00 }, 4, 2);

    CString_ctor(this, aText);
}
