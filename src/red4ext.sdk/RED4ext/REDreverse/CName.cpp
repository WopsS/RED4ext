#include "CName.hpp"

#include "RED4ext/REDfunc.hpp"

const char* RED4ext::REDreverse::CName::ToString(uint64_t aHash)
{
    static REDfunc<char* (*)(uint64_t & aHash)> CNamePool_Get(
      { 0x48, 0x83, 0xEC, 0x38, 0x48, 0x8B, 0x11, 0x48, 0x8D, 0x4C, 0x24, 0x20, 0xE8 }, 1);

    return CNamePool_Get(aHash);
}

