#include "ScriptCompiler.hpp"

ScriptCompilerSourceRef::ScriptCompilerSourceRef(SccApi& api, SccOutput* output, SccSourceRef* sourceRef)
    : m_scc(api)
    , m_output(output)
    , m_sourceRef(sourceRef)
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

ScriptCompilerOutput::ScriptCompilerOutput(SccApi& api, SccResult* result, SccOutput* output, Key key)
    : m_scc(api)
    , m_output(output)
    , m_result(result)
{
}

ScriptCompilerOutput::~ScriptCompilerOutput()
{
    m_scc.free_result(m_result);
}

size_t ScriptCompilerOutput::GetSourceRefCount() const
{
    return m_scc.output_source_ref_count(m_output);
}

ScriptCompilerSourceRef ScriptCompilerOutput::GetSourceRef(size_t index) const
{
    auto sourceRef = m_scc.output_get_source_ref(m_output, index);
    return ScriptCompilerSourceRef(m_scc, m_output, sourceRef);
}

ScriptCompilerFailure::ScriptCompilerFailure(SccApi& scc, SccResult* m_result, Key key)
    : m_scc(scc)
    , m_result(m_result)
{
    char buffer[256] = {0};
    m_scc.copy_error(m_result, buffer, sizeof(buffer));

    auto errorMessage = std::string(buffer);

    // truncate to first line to keep it short
    auto lineEnd = errorMessage.find('\n');
    if (lineEnd != std::string::npos)
    {
        errorMessage.resize(lineEnd);
    }

    // replace trailing characters with ellipsis
    if (errorMessage.length() > sizeof(buffer) - 4)
    {
        errorMessage.resize(sizeof(buffer) - 4);
        errorMessage.append("...");
    }

    m_message = errorMessage;
}

ScriptCompilerFailure::~ScriptCompilerFailure()
{
    m_scc.free_result(m_result);
}

const std::string& ScriptCompilerFailure::GetMessage() const
{
    return m_message;
}

ScriptCompilerSettings::ScriptCompilerSettings(SccApi& m_scc, std::u8string r6Path)
    : m_scc(m_scc)
    , m_r6Path(r6Path)
{
}

ScriptCompilerSettings* ScriptCompilerSettings::AddScriptPath(std::u8string path)
{
    m_scriptPaths.emplace_back(path);
    return this;
}

ScriptCompilerSettings* ScriptCompilerSettings::SetCustomCacheFile(std::u8string path)
{
    m_customCacheFile = path;
    return this;
}

ScriptCompilerSettings::Result ScriptCompilerSettings::Compile()
{
    const auto settings = m_scc.settings_new(reinterpret_cast<const char*>(m_r6Path.c_str()));

    if (!m_customCacheFile.empty())
    {
        m_scc.settings_set_custom_cache_file(settings, reinterpret_cast<const char*>(m_customCacheFile.c_str()));
    }

    for (const auto& path : m_scriptPaths)
    {
        m_scc.settings_add_script_path(settings, reinterpret_cast<const char*>(path.c_str()));
    }

    auto result = m_scc.compile(settings);

    if (auto output = m_scc.get_success(result))
    {
        return ScriptCompilerSettings::Result(std::in_place_type<ScriptCompilerOutput>, m_scc, result, output,
                                              ScriptCompilerOutput::Key());
    }
    else
    {
        return ScriptCompilerSettings::Result(std::in_place_type<ScriptCompilerFailure>, m_scc, result,
                                              ScriptCompilerFailure::Key());
    }
}
