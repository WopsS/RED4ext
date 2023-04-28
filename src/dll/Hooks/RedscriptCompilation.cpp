#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "RedscriptCompilation.hpp"
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

void* _RedscriptCompilation_Run(void* scriptCompilation, RED4ext::CString* command, StringThing* args,
                                RED4ext::CString* currentDirectory, char a5);
Hook<decltype(&_RedscriptCompilation_Run)> RedscriptCompilation_Run(Addresses::RedscriptCompilation_Run,
                                                                         &_RedscriptCompilation_Run);

void* _RedscriptCompilation_Run(void* scriptCompilation, RED4ext::CString* command, StringThing* args,
                     RED4ext::CString* currentDirectory, char a5)
{
    auto paths = App::Get()->GetScriptSystem()->GetPaths();
    for (auto& path : paths)
    {
        wsprintf(args->str, L"%s -compile \"%s\"", args->str, path.c_str());
    }
    args->unk = args->length = wcslen(args->str);

    auto result = RedscriptCompilation_Run(scriptCompilation, command, args, currentDirectory, a5);

    return result;
}
} // namespace

bool Hooks::RedscriptCompilation::Attach()
{
    spdlog::trace("Trying to attach the hook for the redscript compilation at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::RedscriptCompilation_Run));

    auto result = RedscriptCompilation_Run.Attach();
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
                  RED4EXT_OFFSET_TO_ADDR(Addresses::RedscriptCompilation_Run));

    auto result = RedscriptCompilation_Run.Detach();
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
