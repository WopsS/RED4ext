#include <RED4ext/REDreverse/Scripting/StackFrame.hpp>

#include <RED4ext/REDfunc.hpp>

namespace
{
    using namespace RED4ext::REDreverse;
    using CScriptableStackFrame_ctor_t = CScriptableStackFrame* (*)(CScriptableStackFrame* aThis,
                                                                    const Scripting::IScriptable* aScriptable,
                                                                    const CScriptableStackFrame::CStackType* aArgs,
                                                                    uint32_t aArgsCount,
                                                                    CScriptableStackFrame::CStackType* aResult,
                                                                    int64_t a6);
}

CScriptableStackFrame* RED4ext::REDreverse::CScriptableStackFrame::Construct(
  CScriptableStackFrame* aThis, const Scripting::IScriptable* aScriptable, const CStackType* aArgs,
  uint32_t aArgsCount, CStackType* aResult, int64_t a6)
{
    static RED4ext::REDfunc<CScriptableStackFrame_ctor_t> CScriptableStackFrame_ctor(
      { 0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x74, 0x24, 0x10, 0x57, 0x48, 0x83, 0xEC, 0x20,
        0x48, 0x8D, 0x05, 0xCC, 0xCC, 0xCC, 0xCC, 0x48, 0xC7, 0x41, 0x08, 0x00, 0x00, 0x00, 0x00 },
      3, 1);

    return CScriptableStackFrame_ctor(aThis, aScriptable, aArgs, aArgsCount, aResult, a6);
}
