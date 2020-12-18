#include <RED4ext/REDreverse/GameEngine.hpp>

#include <RED4ext/REDptr.hpp>

namespace
{
    RED4ext::REDptr<RED4ext::REDreverse::CGameEngine*> gameEngine({ 0x48, 0x89, 0x05, 0xCC, 0xCC, 0xCC, 0xCC,
                                                                    0x49, 0x8D, 0x9D, 0x88, 0x00, 0x00, 0x00,
                                                                    0x49, 0x8B, 0x07, 0x4C, 0x8B, 0xC3 },
                                                                  1, 3);
}

RED4ext::REDreverse::CGameEngine* RED4ext::REDreverse::CGameEngine::Get()
{
    return gameEngine;
}
