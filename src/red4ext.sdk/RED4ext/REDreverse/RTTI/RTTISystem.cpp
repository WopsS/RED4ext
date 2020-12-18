#include <RED4ext/REDfunc.hpp>
#include <RED4ext/REDreverse/RTTI/RTTISystem.hpp>

namespace
{
    using CRTTISystem_Get_t = RED4ext::REDreverse::CRTTISystem* (*)();
    RED4ext::REDfunc<CRTTISystem_Get_t> CRTTISystem_Get({ 0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x65, 0x48,
                                                          0x8B, 0x04, 0x25, 0x58, 0x00, 0x00, 0x00, 0x48,
                                                          0x8D, 0x1D, 0xCC, 0xCC, 0xCC, 0xCC },
                                                        1);
}

RED4ext::REDreverse::CRTTISystem* RED4ext::REDreverse::CRTTISystem::Get()
{
    return CRTTISystem_Get();
}
