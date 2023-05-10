#pragma once

#include "Hook.hpp"
#include "ISystem.hpp"
#include "Paths.hpp"
#include "PluginBase.hpp"

struct FixedWString
{
    uint32_t length;
    uint32_t maxLength;
    const wchar_t* str;
};

// aFlags is initially 0
enum class ExecuteProcess_Flags : unsigned char
{
    // unsets CREATE_NO_WINDOW
    ShouldCreateWindow = 0x1,
    // sets CREATE_BREAKAWAY_FROM_JOB | CREATE_SUSPENDED in Process Creation Flags
    BreakawayAndSuspend = 0x2,
    Unk3 = 0x3,
    // unsets bInheritHandles
    NoInheritHandles = 0x4,
};

DEFINE_ENUM_FLAG_OPERATORS(ExecuteProcess_Flags)

struct ScriptCompilation
{
  wchar_t command[4096];
  PHANDLE readPipe;
  PHANDLE writePipe;
  HANDLE handle;
  HANDLE hThread;
  uint64_t unk2;
  DWORD errorCode;
};

class ScriptCompilationSystem : public ISystem
{
public:
    ScriptCompilationSystem(const Paths& aPaths);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, const wchar_t* aPath);

    void SetScriptsBlob(const std::filesystem::path& aPath);
    const std::filesystem::path& GetScriptsBlob() const;

    std::wstring GetCompilationArgs(const FixedWString& aOriginal);

private:
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, std::filesystem::path>;
    using MapIter_t = Map_t::iterator;

    void Add(std::shared_ptr<PluginBase> aPlugin, std::filesystem::path path);

    const Paths& m_paths;

    std::mutex m_mutex;
    Map_t m_scriptPaths;
    bool m_hasScriptsBlob;
    std::filesystem::path m_scriptsBlobPath;
};
