#include <RED4ext/REDreverse/Function.hpp>

#include <RED4ext/REDarray.hpp>
#include <RED4ext/REDfunc.hpp>

namespace
{
    using namespace RED4ext::REDreverse;
    using CBaseFunction_Execute_t = bool (*)(CBaseFunction* aThis, CScriptableStackFrame* aStack);
}

bool RED4ext::REDreverse::CBaseFunction::Call(CScriptableStackFrame* aStack)
{
    static RED4ext::REDfunc<CBaseFunction_Execute_t> CBaseFunction_Execute({ 0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48,
                                                                             0x81, 0xEC, 0x90, 0x01, 0x00, 0x00, 0xF6,
                                                                             0x41, 0x78, 0x01, 0x48, 0x8B, 0xDA },
                                                                           1);
    return CBaseFunction_Execute(this, aStack);
}
