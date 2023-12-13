#pragma once

#include <string>
#include "Systems/ScriptCompilationSystem.hpp"
#include "RED4ext/Scripting/ScriptReport.hpp"

namespace Hooks::ValidateScripts
{
bool Attach();
bool Detach();
} // namespace Hooks::ValidateScripts

enum class ValidationErrorType {
    MissingClass,
    MissingGlobalFunction,
    MissingMethod,
    MissingProperty,
    MissingBaseClass,
    MismatchingPropertyType,
    MismatchingBaseClass,
    Unknown
};

struct ValidationError {
    ValidationErrorType type;
    std::string name;
    std::string parent;

    static ValidationError FromString(const char *str);
    std::optional<SourceRef> GetSourceRef() const;
};

std::string WriteValidationMessage(RED4ext::ScriptReport &aReport);
