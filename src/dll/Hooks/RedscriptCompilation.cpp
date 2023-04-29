#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "RedscriptCompilation.hpp"
#include "Systems/ScriptSystem.hpp"
#include "stdafx.hpp"

namespace
{
bool isAttached = false;

struct StringThing
{
    uint32_t length;
    uint32_t unk;
    wchar_t* str;
};

void* _Scripts_RedscriptCompile(void* scriptCompilation, RED4ext::CString* command, StringThing* args,
                                RED4ext::CString* currentDirectory, char a5);
Hook<decltype(&_Scripts_RedscriptCompile)> Scripts_RedscriptCompile(Addresses::Scripts_RedscriptCompile,
                                                                    &_Scripts_RedscriptCompile);

void* _Scripts_RedscriptCompile(void* scriptCompilation, RED4ext::CString* command, StringThing* args,
                                RED4ext::CString* currentDirectory, char a5)
{
    wchar_t* original = args->str;
    wchar_t buffer[ScriptSystem::strLengthMax] = {0};
    auto scriptSystem = App::Get()->GetScriptSystem();
    if (scriptSystem->usingRedmod)
    {
        spdlog::info("Using RedMod configuration");
        scriptSystem->GetRedModArgs(buffer);
    }
    else
    {
        wcscpy_s(buffer, args->str);
    }
    auto paths = scriptSystem->GetPaths();
    for (auto& path : paths)
    {
        spdlog::info("Adding redscript path: '{}'", path.string().c_str());
        wsprintf(buffer, L"%s -compile \"%s\"", buffer, path.wstring().c_str());
    }
    args->str = buffer;
    args->unk = args->length = wcslen(buffer);

    spdlog::info(L"Final redscript compilation args: '{}'", args->str);
    auto result = Scripts_RedscriptCompile(scriptCompilation, command, args, currentDirectory, a5);

    args->str = original;
    args->unk = args->length = wcslen(original);

    if (scriptSystem->usingRedmod && scriptSystem->engine) {
        scriptSystem->engine->scriptsBlobPath = scriptSystem->scriptsBlobPath;
    }

    return result;
}
} // namespace

bool Hooks::RedscriptCompilation::Attach()
{
    spdlog::trace("Trying to attach the hook for the redscript compilation at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Scripts_RedscriptCompile));

    auto result = Scripts_RedscriptCompile.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the redscript compilation. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the redscript compilation was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::RedscriptCompilation::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the redscript compilation at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Scripts_RedscriptCompile));

    auto result = Scripts_RedscriptCompile.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the redscript compilation. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the redscript compilation was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
