#pragma once

#include "Api.hpp"
#include "HookingManager.hpp"
#include "TrampolinesManager.hpp"
#include "PluginBase.hpp"

class PluginsManager
{
public:
    PluginsManager(HookingManager* aHookingManager, TrampolinesManager* aTrampolinesManager);
    ~PluginsManager();

    void LoadAll(const std::filesystem::path& aPluginsDir);
    void UnloadAll();

    std::shared_ptr<PluginBase> GetPlugin(RED4ext::PluginHandle aHandle);
    std::shared_ptr<PluginBase> GetPlugin(const wchar_t* aName);

    const RED4ext::v1::IHooking* GetV1Hooking();
    const RED4ext::v1::ITrampoline* GetV1Trampoline();

private:
    using Load_t = bool (*)(RED4ext::PluginHandle, const void*);
    using Unload_t = void (*)();
    using Query_t = void (*)(void*);
    using Supports_t = uint32_t (*)();

    void Load(const std::filesystem::path& aPath);
    void Unload(const std::shared_ptr<PluginBase> aPlugin);

    HookingManager* m_hookingManager;
    TrampolinesManager* m_trampolinesManager;

    RED4ext::v1::IRED4ext m_v1Interface;
    RED4ext::v1::IHooking m_v1Hooking;
    RED4ext::v1::ITrampoline m_v1Trampoline;

    std::unordered_map<RED4ext::PluginHandle, std::shared_ptr<PluginBase>> m_plugins;
    std::unordered_map<std::wstring_view, std::shared_ptr<PluginBase>> m_pluginsByName;

    // Save an instance of the logger for printing unloading messages, the "Unload" method can be called after spdlog
    // release this instance if ref count is 0.
    std::shared_ptr<spdlog::logger> m_logger;
};
