#include "ValidateScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"
#include "RED4ext/Scripting/ScriptReport.hpp"
#include "ScriptValidationError.hpp"

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

    auto message = WritePopupMessage(errors);
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
