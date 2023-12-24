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
    ScriptCompilerSourceRef(SccApi& api, SccOutput* output, SccSourceRef* sourceRef);

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
    ScriptCompilerOutput(SccApi& scc, SccResult* result, SccOutput* output, Key key);
    ScriptCompilerOutput(const ScriptCompilerOutput&) = delete;
    ScriptCompilerOutput& operator=(const ScriptCompilerOutput&) = delete;
    ~ScriptCompilerOutput();

    size_t GetSourceRefCount() const;
    ScriptCompilerSourceRef GetSourceRef(size_t index) const;

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
    ScriptCompilerFailure(SccApi& scc, SccResult* result, Key key);
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

    ScriptCompilerSettings(SccApi& m_scc, std::u8string r6Path);

    ScriptCompilerSettings* AddScriptPath(std::u8string path);
    ScriptCompilerSettings* SetCustomCacheFile(std::u8string path);
    Result Compile();

private:
    SccApi& m_scc;
    std::u8string m_r6Path;
    std::vector<std::u8string> m_scriptPaths;
    std::u8string m_customCacheFile;
};
