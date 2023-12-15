#include "ExecuteProcess.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"
#include <windows.h>

namespace fs = std::filesystem;

namespace
{
bool isAttached = false;

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

    auto sccPath = fs::path(aCommand.c_str());
    auto& sccLib = sccPath.replace_filename("scc_shared.dll");
    auto sccHandle = LoadLibraryA(sccLib.string().c_str());
    if (sccHandle)
    {
        auto scc = scc_load_api(sccHandle);
        return ExecuteScc(sccPath, scc);
    }

    spdlog::info("Could not load the scc library from {}, falling back to the CLI", sccLib.string());

    auto str = App::Get()->GetScriptCompilationSystem()->GetCompilationArgs(aArgs);

    FixedWString newArgs{};
    newArgs.str = str.c_str();
    newArgs.length = str.length();
    newArgs.maxLength = str.capacity();
    spdlog::info(L"Final redscript compilation arg string: '{}'", newArgs.str);
    return Global_ExecuteProcess(a1, aCommand, newArgs, aCurrentDirectory, a5);
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

bool ExecuteScc(fs::path& sccPath, SccApi& scc)
{
    auto r6Dir = sccPath.parent_path().parent_path().parent_path() / "r6";
    auto scriptSystem = App::Get()->GetScriptCompilationSystem();

    auto settings = scc.settings_new(r6Dir.string().c_str());

    if (scriptSystem->HasScriptsBlob())
    {
        scc.settings_set_custom_cache_file(settings, scriptSystem->GetScriptsBlob().string().c_str());
    }

    for (auto [_, path] : scriptSystem->GetScriptPaths())
    {
        scc.settings_add_script_path(settings, path.string().c_str());
    }

    auto result = scc.compile(settings);
    auto output = scc.get_success(result);

    if (output)
    {
        auto& sourceRepo = scriptSystem->GetSourceRefRepository();

        auto count = scc.output_source_ref_count(output);
        for (auto i = 0; i < count; ++i)
        {
            auto ref = scc.output_get_source_ref(output, i);
            if (!scc.source_ref_is_native(output, ref))
            {
                continue;
            }

            auto typeTag = scc.source_ref_type(output, ref);
            auto namePtr = scc.source_ref_name(output, ref);
            auto parentNamePtr = scc.source_ref_parent_name(output, ref);
            auto pathPtr = scc.source_ref_path(output, ref);
            auto line = scc.source_ref_line(output, ref);

            auto file = sourceRepo.RegisterSourceFile(std::string_view(pathPtr.str, pathPtr.len));

            auto nameStr = std::string_view(namePtr.str, namePtr.len);
            auto parentNameStr = std::string_view(parentNamePtr.str, parentNamePtr.len);
            auto sourceRef = SourceRef{file, line};
            switch (typeTag)
            {
            case SCC_SOURCE_REF_TYPE_CLASS:
                sourceRepo.RegisterClass(nameStr, sourceRef);
                break;
            case SCC_SOURCE_REF_TYPE_FIELD:
                sourceRepo.RegisterProperty(nameStr, parentNameStr, sourceRef);
                break;
            case SCC_SOURCE_REF_TYPE_FUNCTION:
                if (parentNameStr.empty())
                {
                    sourceRepo.RegisterFunction(nameStr, sourceRef);
                }
                else
                {
                    sourceRepo.RegisterMethod(nameStr, parentNameStr, sourceRef);
                }
                break;
            }
        }

        spdlog::info("scc invoked successfully, {} source refs were returned", count);

        scc.free_result(result);
        return true;
    }
    else
    {
        char buffer[128] = {0};
        scc.copy_error(result, buffer, sizeof(buffer));

        auto errorMessage = std::string(buffer);

        // truncate to first line to keep it short
        auto lineEnd = errorMessage.find('\n');
        if (lineEnd != std::string::npos)
        {
            errorMessage.resize(lineEnd);
        }

        // replace trailing characters with ellipsis
        if (errorMessage.length() > sizeof(buffer) - 4)
        {
            errorMessage.resize(sizeof(buffer) - 4);
            errorMessage.append("...");
        }

        spdlog::warn("scc invokation failed with an error: {}", errorMessage);

        scc.free_result(result);
        return false;
    }
}
