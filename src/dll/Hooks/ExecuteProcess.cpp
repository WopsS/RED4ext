#include "ExecuteProcess.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptSystem.hpp"
#include "stdafx.hpp"

namespace
{
bool isAttached = false;

struct FixedWString
{
    uint32_t length;
    uint32_t maxLength;
    wchar_t* str;
};

void* _Global_ExecuteProcess(void* a1, RED4ext::CString* aCommand, FixedWString* aArgs,
                             RED4ext::CString* aCurrentDirectory, char a5);
Hook<decltype(&_Global_ExecuteProcess)> Global_ExecuteProcess(Addresses::Global_ExecuteProcess,
                                                              &_Global_ExecuteProcess);

void* _Global_ExecuteProcess(void* a1, RED4ext::CString* aCommand, FixedWString* aArgs,
                             RED4ext::CString* aCurrentDirectory, char a5)
{
    if (strstr(aCommand->c_str(), "scc.exe") == nullptr)
    {
        return Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, a5);
    }
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
    aArgs->maxLength = aArgs->length = wcslen(buffer);

    spdlog::info(L"Final redscript compilation arg string: '{}'", aArgs->str);
    auto result = Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, a5);

    aArgs->str = original;
    aArgs->maxLength = aArgs->length = wcslen(original);

    return result;
}
} // namespace

bool Hooks::ExecuteProcess::Attach()
{
    spdlog::trace("Trying to attach the hook for execute process at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Global_ExecuteProcess));

    auto result = Global_ExecuteProcess.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for execute process. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for execute process was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::ExecuteProcess::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for execute process at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Global_ExecuteProcess));

    auto result = Global_ExecuteProcess.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for execute process. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for execute process was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}
