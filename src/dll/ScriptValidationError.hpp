#pragma once
#include "SourceRefRepository.hpp"

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
