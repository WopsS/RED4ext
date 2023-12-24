#include "ScriptCompilerSourceRef.hpp"

ScriptCompilerSourceRef::ScriptCompilerSourceRef(SccApi& aApi, SccOutput* aOutput, SccSourceRef* aSourceRef)
    : m_scc(aApi)
    , m_output(aOutput)
    , m_sourceRef(aSourceRef)
{
}

uint8_t ScriptCompilerSourceRef::GetType() const
{
    return m_scc.source_ref_type(m_output, m_sourceRef);
}

std::string_view ScriptCompilerSourceRef::GetName() const
{
    auto namePtr = m_scc.source_ref_name(m_output, m_sourceRef);
    return std::string_view(namePtr.str, namePtr.len);
}

std::string_view ScriptCompilerSourceRef::GetParentName() const
{
    auto parentNamePtr = m_scc.source_ref_parent_name(m_output, m_sourceRef);
    return std::string_view(parentNamePtr.str, parentNamePtr.len);
}

std::string_view ScriptCompilerSourceRef::GetPath() const
{
    auto pathPtr = m_scc.source_ref_path(m_output, m_sourceRef);
    return std::string_view(pathPtr.str, pathPtr.len);
}

size_t ScriptCompilerSourceRef::GetLine() const
{
    return m_scc.source_ref_line(m_output, m_sourceRef);
}

bool ScriptCompilerSourceRef::IsNative() const
{
    return m_scc.source_ref_is_native(m_output, m_sourceRef);
}
