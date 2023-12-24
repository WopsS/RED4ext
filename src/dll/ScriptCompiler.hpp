#pragma once
#include <scc.h>

class ScriptCompilerSourceRef
{
public:
    uint8_t GetType() const;
    std::string_view GetName() const;
    std::string_view GetParentName() const;
    std::string_view GetPath() const;
    size_t GetLine() const;
    bool IsNative() const;

private:
    ScriptCompilerSourceRef(SccApi& aApi, SccOutput* aOutput, SccSourceRef* aSourceRef);

    SccApi& m_scc;
    SccOutput* m_output;
    SccSourceRef* m_sourceRef;

    friend class ScriptCompilerOutput;
};

class ScriptCompilerOutput
{
    // Key used to prevent construction of this class outside of ScriptCompilerSettings.
    // This is necessary to construct the resulting std::variant in place.
    struct Key
    {
        explicit Key() = default;
    };

public:
    ScriptCompilerOutput(SccApi& aApi, SccResult* aResult, SccOutput* aOutput, Key aKey);
    ScriptCompilerOutput(const ScriptCompilerOutput&) = delete;
    ScriptCompilerOutput& operator=(const ScriptCompilerOutput&) = delete;
    ~ScriptCompilerOutput();

    size_t GetSourceRefCount() const;
    ScriptCompilerSourceRef GetSourceRef(size_t aIndex) const;

private:
    SccApi& m_scc;
    SccResult* m_result;
    SccOutput* m_output;

    friend class ScriptCompilerSettings;
};

class ScriptCompilerFailure
{
    // Key used to prevent construction of this class outside of ScriptCompilerSettings.
    // This is necessary to construct the resulting std::variant in place.
    struct Key
    {
        explicit Key() = default;
    };

public:
    ScriptCompilerFailure(SccApi& aApi, SccResult* aResult, Key aKey);
    ScriptCompilerFailure(const ScriptCompilerFailure&) = delete;
    ScriptCompilerFailure& operator=(const ScriptCompilerFailure&) = delete;
    ~ScriptCompilerFailure();

    const std::string& GetMessage() const;

private:
    SccApi& m_scc;
    SccResult* m_result;
    std::string m_message;

    friend class ScriptCompilerSettings;
};

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
