#include <stdafx.hpp>
#include <Hooks/CShutdownState.hpp>

#include <REDs/REDhook.hpp>

namespace
{
    bool CShutdownState_Run(uintptr_t aThis, uintptr_t aApp);
    REDext::REDhook<decltype(&CShutdownState_Run)> CShutdownState_Run_h({ 0x48, 0x89, 0x6C, 0x24, 0x18, 0x56, 0x48,
                                                                          0x83, 0xEC, 0x30, 0x48, 0x8B, 0x0D, 0xCC,
                                                                          0xCC, 0xCC, 0xCC },
                                                                        &CShutdownState_Run, 1);

    bool CShutdownState_Run(uintptr_t aThis, uintptr_t aApp)
    {
        return CShutdownState_Run_h(aThis, aApp);
    }
}

void REDext::Hooks::CShutdownState::Attach()
{
    CShutdownState_Run_h.Attach();
}

void REDext::Hooks::CShutdownState::Detach()
{
    CShutdownState_Run_h.Detach();
}
