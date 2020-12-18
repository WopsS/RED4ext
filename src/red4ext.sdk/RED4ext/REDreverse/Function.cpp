#include <RED4ext/REDreverse/Function.hpp>

#include <RED4ext/REDarray.hpp>

namespace
{
    RED4ext::REDarray<uintptr_t> ScriptingFunctions({ 0x8B, 0x15, 0xCC, 0xCC, 0xCC, 0xCC, 0x4C, 0x8D, 0x05, 0xCC, 0xCC,
                                                      0xCC, 0xCC, 0x8D, 0x82, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xC2 },
                                                    2, 9, 0);

    RED4ext::REDarray<uintptr_t> ScriptingFunctionsWithOpcodes({ 0x8B, 0x15, 0xCC, 0xCC, 0xCC, 0xCC, 0x4C,
                                                                 0x8D, 0x05, 0xCC, 0xCC, 0xCC, 0xCC, 0x8D,
                                                                 0x82, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xC2 },
                                                               2, 9, 1);
}

uintptr_t RED4ext::REDreverse::CBaseFunction::GetAddress()
{
    if ((this->flags & 2) == 0)
    {
        return ScriptingFunctions[this->GetRegistrationIndex()];
    }

    return ScriptingFunctionsWithOpcodes[this->GetRegistrationIndex()];
}
