#include "LoadScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"

namespace
{
bool isAttached = false;

bool _CBaseEngine_LoadScripts(RED4ext::CBaseEngine* aEngine, const RED4ext::CString& aPath, uint64_t aTimestamp, uint64_t a4);
Hook<decltype(&_CBaseEngine_LoadScripts)> CBaseEngine_LoadScripts(Addresses::CBaseEngine_LoadScripts,
                                                                  &_CBaseEngine_LoadScripts);

bool _CBaseEngine_LoadScripts(RED4ext::CBaseEngine* aEngine, const RED4ext::CString& aPath, uint64_t aTimestamp, uint64_t a4)
{
    auto scriptCompilationSystem = App::Get()->GetScriptCompilationSystem();
    const auto& scriptsBlobPath = scriptCompilationSystem->GetScriptsBlob();

    if (!scriptsBlobPath.empty())
    {
        return CBaseEngine_LoadScripts(aEngine, scriptsBlobPath.string(), aTimestamp, a4);
    }
    else
    {
        return CBaseEngine_LoadScripts(aEngine, aPath, aTimestamp, a4);
    }
}
} // namespace

bool Hooks::LoadScripts::Attach()
{
    spdlog::trace("Trying to attach the hook for load scripts at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::CBaseEngine_LoadScripts));

    auto result = CBaseEngine_LoadScripts.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for load scripts. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for load scripts was attached");
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

    spdlog::trace("Trying to detach the hook for load scripts at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::CBaseEngine_LoadScripts));

    auto result = CBaseEngine_LoadScripts.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for load scripts. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for load scripts was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
