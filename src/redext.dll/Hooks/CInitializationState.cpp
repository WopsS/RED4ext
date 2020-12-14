#include <stdafx.hpp>
#include <Hooks/CInitializationState.hpp>

#include <REDs/REDhook.hpp>

namespace
{
    bool CInitializationState_Init(uintptr_t aThis, uintptr_t aApp);
    REDext::REDhook<decltype(&CInitializationState_Init)> CInitializationState_Init_h({ 0x40, 0x55, 0x48, 0x8D, 0x6C,
                                                                                        0x24, 0xA9, 0x48, 0x81, 0xEC,
                                                                                        0x90, 0x00, 0x00, 0x00, 0xE8,
                                                                                        0xCC, 0xCC, 0xCC, 0xCC },
                                                                                      &CInitializationState_Init, 1);

    bool CInitializationState_Init(uintptr_t aThis, uintptr_t aApp)
    {
        auto result = CInitializationState_Init_h(aThis, aApp);
        return result;
    }
}

void REDext::Hooks::CInitializationState::Attach()
{
    CInitializationState_Init_h.Attach();
}

void REDext::Hooks::CInitializationState::Detach()
{
    CInitializationState_Init_h.Detach();
}
