#include "ValidateScripts.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"
#include "Systems/ScriptCompilationSystem.hpp"
#include <cstdint>
#include <tsl/ordered_set.h>
#include <windows.h>

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
    auto message = WriteValidationMessage(aReport);
    if (!message.empty()) {
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
        error.type = ValidationErrorType::MismatchingBaseClass;
    }
    else if (sscanf_s(str, "Imported property '%[^.].%[^']' type '%*[^']' does not match with the native one '%*[^']'",
                      name, (int)sizeof(name), parent, (int)sizeof(parent)) == 2)
    {
        error.type = ValidationErrorType::MismatchingPropertyType;
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
    case ValidationErrorType::MismatchingBaseClass:
        return sourceRepo.GetClass(name.c_str());
    case ValidationErrorType::MismatchingPropertyType:
        return sourceRepo.GetProperty(name.c_str(), parent.c_str());
    default:
        return {};
    }
}

std::string WriteValidationMessage(RED4ext::ScriptReport& aReport)
{
    tsl::ordered_set<std::string_view> faultyFiles;

    for (auto i = 0; i < std::max(aReport.errors->size, 1u) - 1; ++i)
    {
        auto err = ValidationError::FromString(aReport.errors->entries[i].c_str());
        auto ref = err.GetSourceRef();
        if (ref) {
            faultyFiles.insert(ref->file);
        }
    }

    if (faultyFiles.empty()) {
        return "";
    }

    std::string message = "Faulty native definitions have been found in these files:\n";
    for (auto file: faultyFiles) {
        fmt::format_to(std::back_inserter(message), "- {}\n", file);
    }
    return message;
}
