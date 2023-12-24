#pragma once
#include "ScriptCompilerFailure.hpp"
#include "ScriptCompilerOutput.hpp"
#include <scc.h>

class ScriptCompilerSettings
{
public:
    using Result = std::variant<ScriptCompilerFailure, ScriptCompilerOutput>;

    ScriptCompilerSettings(SccApi& aApi, std::filesystem::path aR6Path);

    ScriptCompilerSettings* AddScriptPath(std::filesystem::path aPath);
    ScriptCompilerSettings* SetCustomCacheFile(std::filesystem::path aPath);
    Result Compile();

private:
    SccApi& m_scc;
    std::filesystem::path m_r6Path;
    std::vector<std::filesystem::path> m_scriptPaths;
    std::filesystem::path m_customCacheFile;
};
