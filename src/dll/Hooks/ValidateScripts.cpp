#include "ValidateScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"
#include "RED4ext/Scripting/ScriptReport.hpp"

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
            spdlog::error("Script validation error: {} at {}:{}", message, ref->file, ref->line);
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

ValidationError ValidationError::FromString(const char* str)
{
    ValidationError error;

    char name[64] = {0};
    char parent[64] = {0};

    if (sscanf_s(str, "Missing native class '%[^']'", name, (int)sizeof(name)) == 1)
    {
        error.type = ValidationErrorType::MissingClass;
    }
    else if (sscanf_s(str, "Missing native global function '%[^']'", name, (int)sizeof(name)) == 1)
    {
        error.type = ValidationErrorType::MissingGlobalFunction;
    }
    else if (sscanf_s(str, "Missing native function '%[^']' in native class '%[^']'", name, (int)sizeof(name), parent,
                      (int)sizeof(parent)) == 2)
    {
        error.type = ValidationErrorType::MissingMethod;
    }
    else if (sscanf_s(str, "Missing native property '%[^']' in native class '%[^']'", name, (int)sizeof(name), parent,
                      (int)sizeof(parent)) == 2)
    {
        error.type = ValidationErrorType::MissingProperty;
    }
    else if (sscanf_s(str, "Missing base class '%[^']' of native class '%[^']'", parent, (int)sizeof(parent), name,
                      (int)sizeof(name)) == 2)
    {
        error.type = ValidationErrorType::MissingBaseClass;
    }
    else if (sscanf_s(
                 str,
                 "Native class '%[^']' has declared base class '%[^']' that is different than current one '%*[^']'",
                 name, (int)sizeof(name), parent, (int)sizeof(parent)) == 2)
    {
        error.type = ValidationErrorType::BaseClassMismatch;
    }
    else if (sscanf_s(str, "Imported property '%[^.].%[^']' type '%*[^']' does not match with the native one '%*[^']'",
                      parent, (int)sizeof(parent), name, (int)sizeof(name)) == 2)
    {
        error.type = ValidationErrorType::PropertyTypeMismatch;
    }
    else
    {
        error.type = ValidationErrorType::Unknown;
    }

    error.name = name;
    error.parent = parent;

    return error;
}

std::optional<SourceRef> ValidationError::GetSourceRef() const
{
    auto& sourceRepo = App::Get()->GetScriptCompilationSystem()->GetSourceRefRepository();

    try
    {
        switch (type)
        {
        case ValidationErrorType::MissingClass:
            return sourceRepo.GetClass(name.c_str());
        case ValidationErrorType::MissingGlobalFunction:
            return sourceRepo.GetFunction(name.c_str());
        case ValidationErrorType::MissingMethod:
            return sourceRepo.GetMethod(name.c_str(), parent.c_str());
        case ValidationErrorType::MissingProperty:
            return sourceRepo.GetProperty(name.c_str(), parent.c_str());
        case ValidationErrorType::MissingBaseClass:
            return sourceRepo.GetClass(name.c_str());
        case ValidationErrorType::BaseClassMismatch:
            return sourceRepo.GetClass(name.c_str());
        case ValidationErrorType::PropertyTypeMismatch:
            return sourceRepo.GetProperty(name.c_str(), parent.c_str());
        default:
            return {};
        }
    }
    catch (std::out_of_range)
    {
        return {};
    }
}

std::string WritePopupMessage(const std::vector<ValidationError>& errors)
{
    std::unordered_set<std::string_view> faultyFiles;

    for (auto error : errors)
    {
        auto ref = error.GetSourceRef();
        if (ref)
        {
            faultyFiles.insert(ref->file);
        }
    }

    if (faultyFiles.empty())
    {
        return "";
    }

    std::string message =
        "The scripts below contain invalid native definitions and will prevent your game from starting:\n";
    for (auto file : faultyFiles)
    {
        fmt::format_to(std::back_inserter(message), "- {}\n", file);
    }
    fmt::format_to(std::back_inserter(message),
                   "\n"
                   "Check for updates of the mods that added these files and if you still see this "
                   "message after updating them, they'll have to be uninstalled.\n"
                   "More details about the errors can be found in the logs.\n");
    return message;
}
