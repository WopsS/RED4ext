#include "ExecuteProcess.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"
#include <winbase.h>

namespace
{
bool isAttached = false;

bool _Global_ExecuteProcess(ScriptCompilation* a1, RED4ext::CString& aCommand, FixedWString& aArgs,
                            RED4ext::CString& aCurrentDirectory, ExecuteProcess_Flags aFlags);
Hook<decltype(&_Global_ExecuteProcess)> Global_ExecuteProcess(Addresses::Global_ExecuteProcess,
                                                              &_Global_ExecuteProcess);

bool _Global_ExecuteProcess(ScriptCompilation* a1, RED4ext::CString& aCommand, FixedWString& aArgs,
                            RED4ext::CString& aCurrentDirectory, ExecuteProcess_Flags aFlags)
{
    if (strstr(aCommand.c_str(), "scc.exe") == nullptr)
    {
        return Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, aFlags);
    }

    auto str = App::Get()->GetScriptCompilationSystem()->GetCompilationArgs(aArgs);

    FixedWString newArgs;
    newArgs.str = str.c_str();
    newArgs.length = newArgs.maxLength = wcslen(newArgs.str);

    spdlog::info(L"Final redscript compilation arg string: '{}'", newArgs.str);
    auto result = Global_ExecuteProcess(a1, aCommand, newArgs, aCurrentDirectory, aFlags);

    // 60000 is used in the game
    auto waitResult = WaitForSingleObject(a1->handle, 60000);
    switch (waitResult) {
        case WAIT_TIMEOUT:
            spdlog::error("Redscript compilation timed-out - exiting");
            SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE("Redscript compilation timed-out");
            break;
        case WAIT_ABANDONED:
            spdlog::error("Redscript compilation was abandoned - exiting");
            SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE("Redscript compilation was abandoned");
            break;
        case WAIT_FAILED:
            spdlog::error("Redscript compilation failed - exiting");
            SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE("Redscript compilation failed");
            break;
    }

    GetExitCodeProcess(a1->handle, &a1->errorCode);

    if (a1->errorCode) {
        spdlog::error(L"Redscript compilation was unsuccessful with error code: {} - exiting", a1->errorCode);
        // redscript already showed the error, so we can just exit
        TerminateProcess(GetCurrentProcess(), 1);
    } else {
        spdlog::info(L"Redscript compilation executed successfully");
    }

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
