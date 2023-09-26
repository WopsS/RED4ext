#include "InitScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"

namespace
{
bool isAttached = false;

void* _CBaseEngine_InitScripts(RED4ext::CBaseEngine* aThis, const RED4ext::CString& aScriptsBlobPath, int8_t a3,
                               int16_t a4);
Hook<decltype(&_CBaseEngine_InitScripts)> CBaseEngine_InitScripts(Addresses::CBaseEngine_InitScripts,
                                                                  &_CBaseEngine_InitScripts);

void* _CBaseEngine_InitScripts(RED4ext::CBaseEngine* aThis, const RED4ext::CString& aScriptsBlobPath, int8_t a3,
                               int16_t a4)
{
    auto scriptCompilationSystem = App::Get()->GetScriptCompilationSystem();
    RED4ext::CString original(aThis->scriptsBlobPath);

    if (aThis->scriptsBlobPath.Length())
    {
        spdlog::info("Scripts BLOB is set to '{}'", aThis->scriptsBlobPath.c_str());
        scriptCompilationSystem->SetScriptsBlob(aThis->scriptsBlobPath.c_str());
        aThis->scriptsBlobPath = "";
    }

    auto result = CBaseEngine_InitScripts(aThis, aScriptsBlobPath, a3, a4);
    aThis->scriptsBlobPath = original;
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
