#include "ValidateScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "RED4ext/Scripting/ScriptReport.hpp"
#include "Systems/ScriptCompilationSystem.hpp"

namespace
{
bool isAttached = false;

bool _ScriptValidator_Validate(uint64_t self, uint64_t a1, RED4ext::ScriptReport& aReport);
Hook<decltype(&_ScriptValidator_Validate)> ScriptValidator_Validate(Addresses::ScriptValidator_Validate,
                                                                    &_ScriptValidator_Validate);

bool _ScriptValidator_Validate(uint64_t self, uint64_t a1, RED4ext::ScriptReport& aReport)
{
    aReport.fillErrors = true;
    auto result = ScriptValidator_Validate(self, a1, aReport);
    std::vector<ValidationError> errors;

    for (auto i = 0; i < std::max(aReport.errors->size, 1u) - 1; ++i)
    {
        auto message = aReport.errors->entries[i].c_str();
        auto error = ValidationError::FromString(message);
        errors.push_back(error);

        auto ref = error.GetSourceRef();
        if (ref)
        {
            spdlog::error("Script validation error: {} at {}:{}", message, ref->file, ref->line + 1);
        }
        else
        {
            spdlog::error("Script validation error: {}", message);
        }
    }

    auto& incompatiblePlugins = App::Get()->GetPluginSystem()->GetIncompatiblePlugins();
    auto message = WritePopupMessage(errors, incompatiblePlugins);
    if (!message.empty())
    {
        MessageBoxA(0, message.c_str(), "Script Validation Error", MB_OK | MB_ICONERROR);
    }

    return result;
}
} // namespace

bool Hooks::ValidateScripts::Attach()
{
    spdlog::trace("Trying to attach the hook for validate scripts at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::ScriptValidator_Validate));

    auto result = ScriptValidator_Validate.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for validate scripts. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for validate scripts was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::ValidateScripts::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for validate scripts at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::ScriptValidator_Validate));

    auto result = ScriptValidator_Validate.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for validate scripts. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for validate scripts was detached");
    }

    isAttached = result != NO_ERROR;
    return !isAttached;
}

std::string WritePopupMessage(const std::vector<ValidationError>& validationErrors,
                              const std::vector<PluginSystem::PluginName>& incompatiblePlugins)
{
    if (validationErrors.empty())
    {
        return {};
    }

    std::string message;

    if (!incompatiblePlugins.empty())
    {
        fmt::format_to(std::back_inserter(message),
                       "The following red4ext plugins could not be loaded because they are "
                       "incompatible with the current version of the game:\n");

        for (const auto& plugin : incompatiblePlugins)
        {
            fmt::format_to(std::back_inserter(message), L"- {}\n", plugin);
        }
        fmt::format_to(std::back_inserter(message), "\n");
    }

    std::unordered_set<std::string_view> faultyScriptFiles;

    for (const auto& error : validationErrors)
    {
        auto ref = error.GetSourceRef();
        if (ref)
        {
            faultyScriptFiles.insert(ref->file);
        }
    }

    if (!faultyScriptFiles.empty())
    {
        fmt::format_to(std::back_inserter(message),
                       "The following scripts contain invalid native definitions and will prevent "
                       "your game from starting:\n");
        for (const auto& file : faultyScriptFiles)
        {
            fmt::format_to(std::back_inserter(message), "- {}\n", file);
        }
        fmt::format_to(std::back_inserter(message), "\n");
    }

    fmt::format_to(std::back_inserter(message),
                   "Check if these mods are up-to-date and installed correctly. If you keep seeing "
                   "this message after updating/re-installing them, you might have to remove them "
                   "in order to play the game.\n"
                   "More details can be found in the red4ext logs.\n");

    return message;
}
