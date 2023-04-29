#include "LoadScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptSystem.hpp"
#include "stdafx.hpp"

namespace
{
bool isAttached = false;

bool _Scripts_Load(RED4ext::CBaseEngine* aEngine, RED4ext::CString* aPath, uint64_t aTimestamp, uint64_t a4);
Hook<decltype(&_Scripts_Load)> Scripts_Load(Addresses::Scripts_Load, &_Scripts_Load);

bool _Scripts_Load(RED4ext::CBaseEngine* aEngine, RED4ext::CString* aPath, uint64_t aTimestamp, uint64_t a4)
{
    auto scriptSystem = App::Get()->GetScriptSystem();
    if (scriptSystem->IsUsingRedmod())
    {
        return Scripts_Load(aEngine, scriptSystem->GetScriptsBlobPath(), aTimestamp, a4);
    }
    else
    {
        return Scripts_Load(aEngine, aPath, aTimestamp, a4);
    }
}
} // namespace

bool Hooks::LoadScripts::Attach()
{
    spdlog::trace("Trying to attach the hook for redscript loading at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Scripts_Load));

    auto result = Scripts_Load.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for redscript loading. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for redscript loading was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::LoadScripts::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for redscript loading at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Scripts_Load));

    auto result = Scripts_Load.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for redscript loading. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for redscript loading was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
