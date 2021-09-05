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

void PluginsManager::PreloadAll(const std::filesystem::path& aPluginsDir)
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
            Preload(path);
        }
    }
}

void PluginsManager::LoadAll(const std::filesystem::path& aPluginsDir)
{
    for (const auto handle : m_preloadedPlugins)
    {
        Load(handle);
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

void PluginsManager::Preload(const std::filesystem::path& aPath)
{
    auto filename = aPath.filename();
    auto handle = LoadLibrary(aPath.c_str());
    if (!handle)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::warn(L"'{}' could not be loaded, error: 0x{:X}, description: {}", filename.c_str(), err, errMsg);
        return;
    }

    m_preloadedPlugins.emplace_back(handle);
}

void PluginsManager::Load(const RED4ext::PluginHandle aHandle)
{
    if (!aHandle)
    {
        return;
    }

    wchar_t filename[MAX_PATH + 1];
    auto length = GetModuleFileName(aHandle, filename, static_cast<uint32_t>(std::size(filename)) - 1);

    auto supports = reinterpret_cast<Supports_t>(GetProcAddress(aHandle, "Supports"));
    if (!supports)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::warn(L"'{}' could not be loaded, error: 0x{:X}, description: {}", filename, err, errMsg);
        FreeLibrary(aHandle);

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
        spdlog::warn(L"An exception occured while trying to get API version of '{}'", filename);
    }
    catch (...)
    {
        spdlog::warn(L"An error occured while trying to get API version of '{}', the plugin will not be loaded",
                     filename);
    }

    if (!success)
    {
        FreeLibrary(aHandle);
        return;
    }

    if (apiVersion < MINIMUM_API_VERSION || apiVersion > LATEST_API_VERSION)
    {
        spdlog::warn(L"'{}' reported unsupported API version ({})", filename, apiVersion);
        FreeLibrary(aHandle);

        return;
    }

    std::shared_ptr<PluginBase> plugin;
    const void* extInterface = nullptr;

    switch (apiVersion)
    {
    case RED4EXT_API_VERSION_0:
    {
        plugin = std::make_shared<v0::Plugin>(aHandle);
        extInterface = &m_v0Interface;

        break;
    }
    default:
    {
        assert(false);
        break;
    }
    }

    auto query = reinterpret_cast<Query_t>(GetProcAddress(aHandle, "Query"));
    if (!query)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::debug(L"Could not retrieve 'Query' function from '{}', error: 0x{:X}, description: {}",
                      filename, err, errMsg);
        FreeLibrary(aHandle);

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
        spdlog::warn(L"An exception occured while querying '{}'", filename);
    }
    catch (...)
    {
        spdlog::warn(L"An exception occured while querying '{}'", filename);
    }

    if (!success)
    {
        FreeLibrary(aHandle);
        return;
    }

    auto name = plugin->GetName();
    if (name.empty())
    {
        spdlog::warn(L"'{}' did not supply a name, the plugin will not be loaded", filename);
        FreeLibrary(aHandle);

        return;
    }

    if (plugin->GetAuthor().empty())
    {
        spdlog::warn(L"{} did not supply an author, the plugin will not be loaded", name);
        FreeLibrary(aHandle);

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

        FreeLibrary(aHandle);

        return;
    }

    const auto sdk = plugin->GetSdk();
    if (sdk < MINIMUM_SDK_VERSION || sdk > LATEST_SDK_VERSION)
    {
        spdlog::warn(L"{} (version: {}) is built with an incompatible SDK version ({})", name, std::to_wstring(version),
                     std::to_wstring(sdk));
        FreeLibrary(aHandle);

        return;
    }

    auto load = reinterpret_cast<Load_t>(GetProcAddress(aHandle, "Load"));
    if (!load)
    {
        auto err = GetLastError();
        auto errMsg = Utils::FormatErrorMessage(err);

        spdlog::debug(L"Could not retrieve 'Load' function from {}, error: 0x{:X}, description: {}", name, err, errMsg);
        return;
    }

    m_plugins.emplace(aHandle, plugin);
    m_pluginsByName.emplace(name, plugin);

    success = false;
    try
    {
        if (!load(aHandle, extInterface))
        {
            m_plugins.erase(aHandle);
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
        m_plugins.erase(aHandle);
        m_pluginsByName.erase(name);

        FreeLibrary(aHandle);
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
