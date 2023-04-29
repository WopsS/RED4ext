#include "RedscriptCompilation.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
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

void* _Scripts_RedscriptCompile(void* a1, RED4ext::CString* aCommand, StringThing* aArgs,
                                RED4ext::CString* aCurrentDirectory, char a5);
Hook<decltype(&_Scripts_RedscriptCompile)> Scripts_RedscriptCompile(Addresses::Scripts_RedscriptCompile,
                                                                    &_Scripts_RedscriptCompile);

void* _Scripts_RedscriptCompile(void* a1, RED4ext::CString* aCommand, StringThing* aArgs,
                                RED4ext::CString* aCurrentDirectory, char a5)
{
    wchar_t* original = aArgs->str;
    wchar_t buffer[RED4EXT_SCRIPT_ARGS_MAX_LENGTH] = {0};
    auto scriptSystem = App::Get()->GetScriptSystem();
    if (scriptSystem->IsUsingRedmod())
    {
        spdlog::info("Using RedMod configuration");
        scriptSystem->WriteRedModArgs(buffer);
    }
    else
    {
        wcscpy_s(buffer, aArgs->str);
    }
    auto paths = scriptSystem->GetPaths();
    spdlog::info("Adding paths to redscript compilation:");
    for (auto& path : paths)
    {
        spdlog::info("  '{}'", path.string().c_str());
        wsprintf(buffer, L"%s -compile \"%s\"", buffer, path.wstring().c_str());
    }
    aArgs->str = buffer;
    aArgs->unk = aArgs->length = wcslen(buffer);

    spdlog::info(L"Final redscript compilation arg string: '{}'", aArgs->str);
    auto result = Scripts_RedscriptCompile(a1, aCommand, aArgs, aCurrentDirectory, a5);

    aArgs->str = original;
    aArgs->unk = aArgs->length = wcslen(original);

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
