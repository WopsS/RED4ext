#include "InitScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptSystem.hpp"
#include "stdafx.hpp"

namespace
{
bool isAttached = false;

void* _CBaseEngine_InitScripts(RED4ext::CBaseEngine* aEngine, unsigned __int8 a2, unsigned __int16 a3);
Hook<decltype(&_CBaseEngine_InitScripts)> CBaseEngine_InitScripts(Addresses::CBaseEngine_InitScripts,
                                                                  &_CBaseEngine_InitScripts);

void* _CBaseEngine_InitScripts(RED4ext::CBaseEngine* aEngine, unsigned __int8 a2, unsigned __int16 a3)
{
    auto scriptSystem = App::Get()->GetScriptSystem();
    auto original = aEngine->scriptsBlobPath;
    if (aEngine->scriptsBlobPath.Length())
    {
        spdlog::info("Found scriptsBlobPath: '{}'", aEngine->scriptsBlobPath.c_str());
        scriptSystem->SetUsingRedmod(true);
        scriptSystem->SetScriptsBlobPath(aEngine->scriptsBlobPath);
        aEngine->scriptsBlobPath = "";
    }

    auto result = CBaseEngine_InitScripts(aEngine, a2, a3);
    aEngine->scriptsBlobPath = original;
    return result;
}
} // namespace

bool Hooks::InitScripts::Attach()
{
    spdlog::trace("Trying to attach the hook for init scripts at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::CBaseEngine_InitScripts));

    auto result = CBaseEngine_InitScripts.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for init scripts. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for init scripts was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::InitScripts::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for init scripts at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::CBaseEngine_InitScripts));

    auto result = CBaseEngine_InitScripts.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for init scripts. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for init scripts was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
