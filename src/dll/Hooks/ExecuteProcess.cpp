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

bool _Global_ExecuteProcess(void* a1, RED4ext::CString* aCommand, FixedWString* aArgs,
                            RED4ext::CString* aCurrentDirectory, char a5);
Hook<decltype(&_Global_ExecuteProcess)> Global_ExecuteProcess(Addresses::Global_ExecuteProcess,
                                                              &_Global_ExecuteProcess);

bool _Global_ExecuteProcess(void* a1, RED4ext::CString* aCommand, FixedWString* aArgs,
                            RED4ext::CString* aCurrentDirectory, char a5)
{
    if (strstr(aCommand->c_str(), "scc.exe") == nullptr)
    {
        return Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, a5);
    }
    std::wstring original = aArgs->str;
    std::wstring buffer;
    auto scriptSystem = App::Get()->GetScriptSystem();
    if (scriptSystem->IsUsingRedmod())
    {
        spdlog::info("Using RedMod configuration");
        buffer = scriptSystem->WriteRedModArgs();
    }
    else
    {
        buffer = aArgs->str;
    }
    auto paths = scriptSystem->GetPaths();
    spdlog::info("Adding paths to redscript compilation:");
    for (auto& path : paths)
    {
        spdlog::info("  '{}'", path.string());
        buffer += LR"( -compile ")" + path.wstring() + L'"';
        if (buffer.size() + aCommand->Length() > RED4EXT_SCRIPT_ARGS_MAX_LENGTH)
        {
            spdlog::error("Redscript compilation command is too long:");
            spdlog::error(L"{}", buffer);
            SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(
                "During RED4ext's redscript compilation command, too many paths were added to the compile "
                "command's string, causing it to exceed the 4096 character limit.\n\nYou'll need to remove "
                "RED4ext mod(s) for the game to launch. See red4ext/logs/red4ext.log for more details.");
            return 1;
        }
    }
    aArgs->str = buffer.data();
    aArgs->maxLength = aArgs->length = buffer.size();

    spdlog::info(L"Final redscript compilation arg string: '{}'", aArgs->str);
    auto result = Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, a5);

    aArgs->str = original.data();
    aArgs->maxLength = aArgs->length = original.size();

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
