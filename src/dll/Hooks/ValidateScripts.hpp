#pragma once

#include "Systems/ScriptCompilationSystem.hpp"

namespace Hooks::ValidateScripts
{
bool Attach();
bool Detach();
} // namespace Hooks::ValidateScripts

enum class ValidationErrorType
{
    MissingClass,
    MissingGlobalFunction,
    MissingMethod,
    MissingProperty,
    MissingBaseClass,
    PropertyTypeMismatch,
    BaseClassMismatch,
    Unknown
};

struct ValidationError
{
    ValidationErrorType type;
    std::string name;
    std::string parent;

    static ValidationError FromString(const char* str);
    std::optional<SourceRef> GetSourceRef() const;
};

std::string WritePopupMessage(const std::vector<ValidationError>& errors);
