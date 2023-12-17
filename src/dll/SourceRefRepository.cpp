#include "SourceRefRepository.hpp"

std::string_view SourceRefRepository::RegisterSourceFile(std::string_view aPath)
{
    return InternString(aPath);
}

void SourceRefRepository::RegisterClass(std::string_view aName, SourceRef aRef)
{
    m_classes.emplace(InternString(aName), aRef);
}

void SourceRefRepository::RegisterProperty(std::string_view aName, std::string_view aParent, SourceRef aRef)
{
    Member key = {.name = InternString(aName), .parent = InternString(aParent)};
    m_fields.emplace(key, aRef);
}

void SourceRefRepository::RegisterMethod(std::string_view aName, std::string_view aParent, SourceRef aRef)
{
    Member key = {.name = InternString(aName), .parent = InternString(aParent)};
    m_methods.emplace(key, aRef);
}

void SourceRefRepository::RegisterFunction(std::string_view aName, SourceRef aRef)
{
    m_functions.emplace(InternString(aName), aRef);
}

const SourceRef& SourceRefRepository::GetClass(std::string_view aName) const
{
    return m_classes.at(aName);
}

const SourceRef& SourceRefRepository::GetProperty(std::string_view aName, std::string_view aParent) const
{
    Member key = {.name = aName, .parent = aParent};
    return m_fields.at(key);
}

const SourceRef& SourceRefRepository::GetMethod(std::string_view aName, std::string_view aParent) const
{
    Member key = {.name = aName, .parent = aParent};
    return m_methods.at(key);
}

const SourceRef& SourceRefRepository::GetFunction(std::string_view aName) const
{
    return m_functions.at(aName);
}

std::string_view SourceRefRepository::InternString(std::string_view aString)
{
    auto it = m_internedStrings.find(aString);
    if (it != m_internedStrings.end())
    {
        return it->first;
    }

    auto ptr = std::make_unique<std::string>(aString);
    std::string_view view = *ptr;
    m_internedStrings.emplace(view, std::move(ptr));
    return view;
}
