#include "ScriptCompilerSettings.hpp"

ScriptCompilerSettings::ScriptCompilerSettings(SccApi& aApi, std::filesystem::path aR6Path)
    : m_scc(aApi)
    , m_r6Path(aR6Path)
{
}

ScriptCompilerSettings* ScriptCompilerSettings::AddScriptPath(std::filesystem::path aPath)
{
    m_scriptPaths.emplace_back(aPath);
    return this;
}

ScriptCompilerSettings* ScriptCompilerSettings::SetCustomCacheFile(std::filesystem::path aPath)
{
    m_customCacheFile = aPath;
    return this;
}

ScriptCompilerSettings::Result ScriptCompilerSettings::Compile()
{
    auto r6PathStr = m_r6Path.u8string();
    const auto settings = m_scc.settings_new(reinterpret_cast<const char*>(r6PathStr.c_str()));

    if (!m_customCacheFile.empty())
    {
        auto customCacheFileStr = m_customCacheFile.u8string();
        m_scc.settings_set_custom_cache_file(settings, reinterpret_cast<const char*>(customCacheFileStr.c_str()));
    }

    for (const auto& path : m_scriptPaths)
    {
        auto pathStr = path.u8string();
        m_scc.settings_add_script_path(settings, reinterpret_cast<const char*>(pathStr.c_str()));
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
