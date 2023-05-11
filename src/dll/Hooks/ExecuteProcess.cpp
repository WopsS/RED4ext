#include "ExecuteProcess.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"

namespace
{
bool isAttached = false;
uint32_t runCount = 0;

bool _RedProcess_Execute(RED4ext::Process* aThis, RED4ext::CString& aCommand,
                            RED4ext::Process::FixedWString& aArgs, RED4ext::CString& aCurrentDirectory,
                            RED4ext::Process::ExecutionFlags aFlags);
Hook<decltype(&_RedProcess_Execute)> RedProcess_Execute(Addresses::RedProcess_Execute,
                                                              &_RedProcess_Execute);

bool _RedProcess_Execute(RED4ext::Process* aThis, RED4ext::CString& aCommand,
                            RED4ext::Process::FixedWString& aArgs, RED4ext::CString& aCurrentDirectory,
                            RED4ext::Process::ExecutionFlags aFlags)
{
    if (strstr(aCommand.c_str(), "scc.exe") == nullptr)
    {
        return RedProcess_Execute(aThis, aCommand, aArgs, aCurrentDirectory, aFlags);
    }

    auto scriptCompilationSystem = App::Get()->GetScriptCompilationSystem();
    auto str = scriptCompilationSystem->GetCompilationArgs(aArgs);

    RED4ext::Process::FixedWString newArgs;
    newArgs.str = str.c_str();
    newArgs.length = newArgs.maxLength = wcslen(newArgs.str);

    spdlog::info(L"Final redscript compilation arg string: '{}'", newArgs.str);
    auto result = RedProcess_Execute(aThis, aCommand, newArgs, aCurrentDirectory, aFlags);

    auto waitResult = WaitForSingleObject(aThis->handle, RED4ext::Process::DefaultTimeout);
    switch (waitResult)
    {
    case WAIT_TIMEOUT:
    {
        spdlog::error("Redscript compilation timed-out - exiting");
        SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE("Redscript compilation timed-out");
        break;
    }
    case WAIT_ABANDONED:
    {
        spdlog::error("Redscript compilation was abandoned - exiting");
        SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE("Redscript compilation was abandoned");
        break;
    }
    case WAIT_FAILED:
    {
        spdlog::error("Redscript compilation failed - exiting");
        SHOW_LAST_ERROR_MESSAGE_AND_EXIT_FILE_LINE("Redscript compilation failed");
        break;
    }
    }

    GetExitCodeProcess(aThis->handle, &aThis->errorCode);

    if (aThis->errorCode)
    {
        spdlog::error(L"Redscript compilation was unsuccessful with error code: {} - exiting", aThis->errorCode);
        // redscript already showed the error, so we can just exit
        if (scriptCompilationSystem->HasScripts() && runCount == 0) {
            TerminateProcess(GetCurrentProcess(), 1);
        }
    }
    else
    {
        spdlog::info(L"Redscript compilation executed successfully");
    }

    runCount++;

    return result;
}
} // namespace

bool Hooks::ExecuteProcess::Attach()
{
    spdlog::trace("Trying to attach the hook for execute process at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::RedProcess_Execute));

    auto result = RedProcess_Execute.Attach();
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
                  RED4EXT_OFFSET_TO_ADDR(Addresses::RedProcess_Execute));

    auto result = RedProcess_Execute.Detach();
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
