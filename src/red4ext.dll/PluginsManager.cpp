#include "stdafx.hpp"
#include "PluginsManager.hpp"
#include "Api.hpp"
#include "Utils.hpp"
#include "v0/Hooking.hpp"
#include "v0/Plugin.hpp"
#include "v0/RED4ext.hpp"
#include "v0/Trampoline.hpp"

PluginsManager::PluginsManager(HookingManager* aHookingManager, TrampolinesManager* aTrampolinesManager)
    : m_hookingManager(aHookingManager)
    , m_trampolinesManager(aTrampolinesManager)
{
    m_v0Interface.GetSDKVersion = &v0::GetSDKVersion;
    m_v0Interface.GetRuntimeVersion = &v0::GetRuntimeVersion;
    m_v0Interface.RegisterInterface = &v0::RegisterInterface;
    m_v0Interface.GetInterface = &v0::GetInterface;
    m_v0Interface.GetHookingInterface = &v0::GetHookingInterface;
    m_v0Interface.GetTrampolineInterface = &v0::GetTrampolineInterface;

    m_v0Hooking.Create = &v0::Hooking::Create;
    m_v0Hooking.Remove = &v0::Hooking::Remove;
    m_v0Hooking.Attach = &v0::Hooking::Attach;
    m_v0Hooking.Detach = &v0::Hooking::Detach;
    m_v0Hooking.FindPattern = &v0::Hooking::FindPattern;

    m_v0Trampoline.Alloc = &v0::Trampoline::Alloc;
    m_v0Trampoline.Free = &v0::Trampoline::Free;
}

PluginsManager::~PluginsManager()
{
    UnloadAll();
}

void PluginsManager::LoadAll(const std::filesystem::path& aPluginsDir)
{
    m_logger = spdlog::default_logger();

    if (!std::filesystem::exists(aPluginsDir))
    {
        std::filesystem::create_directories(aPluginsDir);
    }

    for (const auto& path : std::filesystem::recursive_directory_iterator(aPluginsDir))
    {
        if (path.path().extension() == L".dll")
        {
            Load(path);
        }
    }

    for (const auto& [handle, plugin] : m_plugins)
    {
        PostLoad(plugin);
    }

    m_hookingManager->AttachAll();
}

void PluginsManager::UnloadAll()
{
    for (const auto& [handle, plugin] : m_plugins)
    {
        Unload(plugin);
    }

    m_hookingManager->RemoveAll();
    m_trampolinesManager->FreeAll();

    m_plugins.clear();
    m_pluginsByName.clear();
}

std::shared_ptr<PluginBase> PluginsManager::GetPlugin(RED4ext::PluginHandle aHandle)
{
    auto elem = m_plugins.find(aHandle);
    if (elem != m_plugins.end())
    {
        return elem->second;
    }

    return nullptr;
}

std::shared_ptr<PluginBase> PluginsManager::GetPlugin(const wchar_t* aName)
{
    auto elem = m_pluginsByName.find(aName);
    if (elem != m_pluginsByName.end())
    {
        return elem->second;
    }

    return nullptr;
}

const RED4ext::v0::IHooking* PluginsManager::GetV0Hooking()
{
    return &m_v0Hooking;
}

const RED4ext::v0::ITrampoline* PluginsManager::GetV0Trampoline()
{
    return &m_v0Trampoline;
}

void PluginsManager::Load(const std::filesystem::path& aPath)
{
    if (aPath.extension() != L".dll")
    {
        return;
    }

    auto filename = aPath.filename();

    auto handle = LoadLibrary(aPath.c_str());
    if (!handle)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::warn(L"'{}' could not be loaded, error: 0x{:X}, description: {}", filename.c_str(), err, errMsg);
        return;
    }

    auto supports = reinterpret_cast<Supports_t>(GetProcAddress(handle, "Supports"));
    if (!supports)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::warn(L"'{}' could not be loaded, error: 0x{:X}, description: {}", filename.c_str(), err, errMsg);
        FreeLibrary(handle);

        return;
    }

    uint32_t apiVersion;
    bool success = false;

    try
    {
        apiVersion = supports();
        success = true;
    }
    catch (const std::exception& ex)
    {
        spdlog::warn(ex.what());
        spdlog::warn(L"An exception occured while trying to get API version of '{}'", filename.c_str());
    }
    catch (...)
    {
        spdlog::warn(L"An error occured while trying to get API version of '{}', the plugin will not be loaded",
                     filename.c_str());
    }

    if (!success)
    {
        FreeLibrary(handle);
        return;
    }

    if (apiVersion < MINIMUM_API_VERSION || apiVersion > LATEST_API_VERSION)
    {
        spdlog::warn(L"'{}' reported unsupported API version ({})", filename.c_str(), apiVersion);
        FreeLibrary(handle);

        return;
    }

    std::shared_ptr<PluginBase> plugin;
    const void* extInterface = nullptr;

    switch (apiVersion)
    {
    case RED4EXT_API_VERSION_1:
    {
        plugin = std::make_shared<v0::Plugin>(handle);
        extInterface = &m_v0Interface;

        break;
    }
    default:
    {
        assert(false);
        break;
    }
    }

    auto query = reinterpret_cast<Query_t>(GetProcAddress(handle, "Query"));
    if (!query)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::debug(L"Could not retrieve 'Query' function from '{}', error: 0x{:X}, description: {}",
                      filename.c_str(), err, errMsg);
        FreeLibrary(handle);

        return;
    }

    success = false;
    try
    {
        query(plugin->GetInfoHolder());
        success = true;
    }
    catch (const std::exception& ex)
    {
        spdlog::warn(ex.what());
        spdlog::warn(L"An exception occured while querying '{}'", filename.c_str());
    }
    catch (...)
    {
        spdlog::warn(L"An exception occured while querying '{}'", filename.c_str());
    }

    if (!success)
    {
        FreeLibrary(handle);
        return;
    }

    auto name = plugin->GetName();
    if (name.empty())
    {
        spdlog::warn(L"'{}' did not supply a name, the plugin will not be loaded", filename.c_str());
        FreeLibrary(handle);

        return;
    }

    if (plugin->GetAuthor().empty())
    {
        spdlog::warn(L"{} did not supply an author, the plugin will not be loaded", name);
        FreeLibrary(handle);

        return;
    }

    const auto version = plugin->GetVersion();
    const auto runtime = Utils::GetRuntimeVersion();
    const auto requestedRuntime = plugin->GetRuntime();

    if (requestedRuntime != RED4EXT_RUNTIME_INDEPENDENT && requestedRuntime != runtime)
    {
        spdlog::warn(L"{} (version: {}) is not compatible with the current game version ({}.{}{}), the compatible "
                     L"version is {}.{}{}",
                     name, std::to_wstring(version), runtime.major, runtime.minor, runtime.patch,
                     requestedRuntime.major, requestedRuntime.minor, requestedRuntime.patch);

        FreeLibrary(handle);

        return;
    }

    const auto sdk = plugin->GetSdk();
    if (sdk < MINIMUM_SDK_VERSION || sdk > LATEST_SDK_VERSION)
    {
        spdlog::warn(L"{} (version: {}) is built with an incompatible SDK version ({})", name, std::to_wstring(version),
                     std::to_wstring(sdk));
        FreeLibrary(handle);

        return;
    }

    auto load = reinterpret_cast<Load_t>(GetProcAddress(handle, "Load"));
    if (!load)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::debug(L"Could not retrieve 'Load' function from {}, error: 0x{:X}, description: {}", name, err, errMsg);
        return;
    }

    m_plugins.emplace(handle, plugin);
    m_pluginsByName.emplace(name, plugin);

    success = false;
    try
    {
        if (!load(handle, extInterface))
        {
            m_plugins.erase(handle);
            m_pluginsByName.erase(name);

            spdlog::warn(L"{} could not be loaded, 'Load' returned false", name);
            Unload(plugin);

            return;
        }

        success = true;
    }
    catch (const std::exception& ex)
    {
        spdlog::warn(ex.what());
        spdlog::warn(L"An exception occured while loading '{}'", name);
    }
    catch (...)
    {
        spdlog::warn(L"An error occured while loading '{}'", name);
    }

    if (!success)
    {
        m_plugins.erase(handle);
        m_pluginsByName.erase(name);

        FreeLibrary(handle);
        return;
    }

    spdlog::info(L"{} (version: {}, author: {}) loaded", name, std::to_wstring(version), plugin->GetAuthor());
}

void PluginsManager::PostLoad(const std::shared_ptr<PluginBase> aPlugin)
{
    auto handle = aPlugin->GetHandle();

    auto postLoad = reinterpret_cast<PostLoad_t>(GetProcAddress(handle, "PostLoad"));
    if (postLoad)
    {
        try
        {
            postLoad();
        }
        catch (...)
        {
            auto name = aPlugin->GetName();
            spdlog::warn(L"An error occured on post load in '{}'", name);
        }
    }
}

void PluginsManager::Unload(const std::shared_ptr<PluginBase> aPlugin)
{
    auto handle = aPlugin->GetHandle();
    auto unload = reinterpret_cast<Unload_t>(GetProcAddress(handle, "Unload"));

    if (unload)
    {
        auto name = aPlugin->GetName();

        try
        {
            unload();
            m_logger->info(L"{} unloaded", aPlugin->GetName());
        }
        catch (const std::exception& ex)
        {
            m_logger->warn(ex.what());
            m_logger->warn(L"An exception occured while unloading '{}'", name);
        }
        catch (...)
        {
            m_logger->warn(L"An error occured while unloading '{}'", name);
        }
    }

    m_hookingManager->RemoveAll(aPlugin);
    m_trampolinesManager->FreeAll(aPlugin);

    FreeLibrary(handle);
}
