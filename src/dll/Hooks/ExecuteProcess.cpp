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

bool _Global_ExecuteProcess(void* a1, RED4ext::CString& aCommand, FixedWString& aArgs,
                            RED4ext::CString& aCurrentDirectory, char a5);
Hook<decltype(&_Global_ExecuteProcess)> Global_ExecuteProcess(Addresses::Global_ExecuteProcess,
                                                              &_Global_ExecuteProcess);

bool _Global_ExecuteProcess(void* a1, RED4ext::CString& aCommand, FixedWString& aArgs,
                            RED4ext::CString& aCurrentDirectory, char a5)
{
    if (strstr(aCommand.c_str(), "scc.exe") == nullptr)
    {
        return Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, a5);
    }
    std::wstring original = aArgs.str;
    auto scriptSystem = App::Get()->GetScriptSystem();

    auto buffer = fmt::wmemory_buffer();
    if (scriptSystem->IsUsingRedmod())
    {
        spdlog::info("Using RedMod configuration");
        format_to(std::back_inserter(buffer), scriptSystem->GetRedModArgs());
    }
    else
    {
        format_to(std::back_inserter(buffer), aArgs.str);
    }
    format_to(std::back_inserter(buffer), LR"( -compilePathsFile "{}")", scriptSystem->CreatePathsFile());

    aArgs.str = buffer.data();
    aArgs.maxLength = aArgs.length = buffer.size();

    spdlog::info(L"Final redscript compilation arg string: '{}'", aArgs.str);
    auto result = Global_ExecuteProcess(a1, aCommand, aArgs, aCurrentDirectory, a5);

    aArgs.str = original.data();
    aArgs.maxLength = aArgs.length = original.size();

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
