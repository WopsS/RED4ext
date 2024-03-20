#include "ScriptCompilerOutput.hpp"

ScriptCompilerOutput::ScriptCompilerOutput(SccApi& aApi, SccResult* aResult, SccOutput* aOutput, Key aKey)
    : m_scc(aApi)
    , m_output(aOutput)
    , m_result(aResult)
{
    RED4EXT_UNUSED_PARAMETER(aKey);
}

ScriptCompilerOutput::~ScriptCompilerOutput()
{
    m_scc.free_result(m_result);
}

size_t ScriptCompilerOutput::GetSourceRefCount() const
{
    return m_scc.output_source_ref_count(m_output);
}

ScriptCompilerSourceRef ScriptCompilerOutput::GetSourceRef(size_t aIndex) const
{
    auto sourceRef = m_scc.output_get_source_ref(m_output, aIndex);
    return ScriptCompilerSourceRef(m_scc, m_output, sourceRef);
}
