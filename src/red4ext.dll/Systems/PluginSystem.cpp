#include "stdafx.hpp"
#include "PluginSystem.hpp"
#include "Image.hpp"
#include "Utils.hpp"
#include "Version.hpp"
#include "v0/Plugin.hpp"

#define MINIMUM_API_VERSION RED4EXT_API_VERSION_0
#define LATEST_API_VERSION RED4EXT_API_VERSION_LATEST

#define MINIMUM_SDK_VERSION RED4EXT_SDK_0_3_0
#define LATEST_SDK_VERSION RED4EXT_SDK_LATEST

#define LOG_FS_ERROR(text, ec)                                                                                         \
    auto val = ec.value();                                                                                             \
    const auto& category = ec.category();                                                                              \
    auto msg = category.message(val);                                                                                  \
    spdlog::error(text L". Error code: {}, msg: '{}'", val, Utils::Widen(msg))

#define LOG_FS_ENTRY_ERROR(text, entry, ec)                                                                            \
    auto val = ec.value();                                                                                             \
    const auto& category = ec.category();                                                                              \
    auto msg = category.message(val);                                                                                  \
    spdlog::error(text L". Error code: {}, msg: '{}', entry: '{}'", val, Utils::Widen(msg), entry)

PluginSystem::PluginSystem(const Config::PluginsConfig& aConfig, const Paths& aPaths)
    : m_config(aConfig)
    , m_paths(aPaths)
{
}

ESystemType PluginSystem::GetType()
{
    return ESystemType::Plugin;
}

void PluginSystem::Startup()
{
    if (!m_config.isEnabled)
    {
        return;
    }

    spdlog::trace("Loading plugins...");

    std::error_code ec;

    auto dir = m_paths.GetPluginsDir();
    auto exists = std::filesystem::exists(dir, ec);
    if (ec)
    {
        LOG_FS_ERROR("Could not check the plugins directory existence", ec);
        return;
    }

    if (!exists)
    {
        std::filesystem::create_directories(dir, ec);
        if (ec)
        {
            LOG_FS_ERROR("Could not create the plugins directory", ec);
            return;
        }
    }

    auto iter = std::filesystem::recursive_directory_iterator(
        dir, std::filesystem::directory_options::follow_directory_symlink, ec);

    if (ec)
    {
        LOG_FS_ERROR("Could not create an iterator for the plugins directory", ec);
        return;
    }

    auto end = std::filesystem::end(iter);
    for (; iter != end; iter.increment(ec))
    {
        /*
         * Do not allow something like:
         *  game_root/read4ext/plugins/some_plugin/a_sub_dir/some_plugin.dll
         *  game_root/read4ext/plugins/some_plugin/a_sub_dir/another_sub_dir/some_plugin.dll
         */
        int32_t depth = iter.depth();
        if (depth > 1)
        {
            iter.disable_recursion_pending();
            continue;
        }

        const auto& entry = *iter;
        const auto& path = entry.path();

        if (ec)
        {
            LOG_FS_ENTRY_ERROR(L"Could not fetch a directory entry", path, ec);
            continue;
        }

        // Deal with broken symlinks.
        if (entry.is_symlink(ec))
        {
            if (!entry.exists(ec))
            {
                // Symlink is broken, skip it.
                spdlog::warn(L"Symbolic link is broken, it will be skipped. Symlink: '{}'", path);
                continue;
            }
            else if (ec)
            {
                LOG_FS_ENTRY_ERROR(L"Could not check if the symlink exists", path, ec);
                continue;
            }
        }
        else if (ec)
        {
            LOG_FS_ENTRY_ERROR(L"Could not check if the entry is a symbolic link", path, ec);
            continue;
        }

        if (entry.is_regular_file(ec) && path.extension() == L".dll")
        {
            const auto stem = path.stem();
            if (m_config.ignored.contains(stem))
            {
                spdlog::debug(L"Ignoring plugin '{}' because it is ignored. Path: '{}'", stem, path);
                continue;
            }

            bool searchLoadDir = depth == 1;
            Load(path, searchLoadDir);
        }
        else if (ec)
        {
            LOG_FS_ENTRY_ERROR(L"Could not check if the entry is a regular file", path, ec);
        }
    }

    spdlog::info("{} plugin(s) loaded", m_plugins.size());
}

void PluginSystem::Shutdown()
{
    if (!m_config.isEnabled)
    {
        return;
    }

    auto size = m_plugins.size();
    spdlog::trace("Unloading {} plugin(s)...", size);

    for (auto it = m_plugins.begin(); it != m_plugins.end();)
    {
        it = Unload(it->second);
    }

    spdlog::info("{} plugin(s) unloaded", size);
}

std::shared_ptr<PluginBase> PluginSystem::GetPlugin(HMODULE aModule) const
{
    auto iter = m_plugins.find(aModule);
    if (iter != m_plugins.end())
    {
        return iter->second;
    }

    spdlog::warn("Could not find a plugin with handle {}", fmt::ptr(aModule));
    return nullptr;
}

void PluginSystem::Load(const std::filesystem::path& aPath, bool aSearchLoadDir)
{
    spdlog::trace(L"Loading plugin from '{}'...", aPath);

    uint32_t flags = LOAD_LIBRARY_SEARCH_DEFAULT_DIRS;
    if (aSearchLoadDir)
    {
        flags |= LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR;
    }

    const auto stem = aPath.stem();

    wil::unique_hmodule handle(LoadLibraryEx(aPath.c_str(), nullptr, flags));
    if (!handle)
    {
        auto msg = Utils::FormatLastError();
        spdlog::warn(L"Could not load plugin '{}'. Error code: {}, msg: '{}', path: '{}'", stem, GetLastError(), msg,
                     aPath);
        return;
    }

    spdlog::trace(L"'{}' has loaded into the address space at {}", stem, fmt::ptr(handle.get()));

    auto plugin = CreatePlugin(aPath, std::move(handle));
    if (!plugin)
    {
        // Unsupported API version.
        return;
    }

    if (!plugin->Query())
    {
        // Query failed or some data is invalid.
        return;
    }

    const auto pluginName = plugin->GetName();
    const auto& pluginVersion = plugin->GetVersion();

    const auto image = Image::Get();
    const auto& fileVer = image->GetFileVersion();
    const auto& productVer = image->GetProductVersion();

    const auto& requestedRuntime = plugin->GetRuntimeVersion();
    if (requestedRuntime != RED4EXT_RUNTIME_INDEPENDENT && requestedRuntime != fileVer)
    {
        spdlog::warn(L"{} (version: {}) is not incompatible with the current game's version. This version of the "
                     L"plugin supports only runtime version {}.{}.{}.{}",
                     pluginName, std::to_wstring(pluginVersion), requestedRuntime.major, requestedRuntime.minor,
                     requestedRuntime.build, requestedRuntime.revision);
        return;
    }

    const auto& pluginSdk = plugin->GetSdkVersion();
    if (pluginSdk < MINIMUM_SDK_VERSION || pluginSdk > LATEST_SDK_VERSION)
    {
        spdlog::warn(L"{} (version: {}) uses RED4ext.SDK v{} which is not supported by RED4ext v{}. If you are the "
                     L"plugin's author, recompile the plugin with a version of RED4ext.SDK that meets the following "
                     L"criteria: RED4ext.SDK >= {} && RED4ext.SDK <= {}",
                     pluginName, std::to_wstring(pluginVersion), std::to_wstring(pluginSdk), TEXT(RED4EXT_VERSION_STR),
                     std::to_wstring(MINIMUM_SDK_VERSION), std::to_wstring(LATEST_SDK_VERSION));
        return;
    }

    auto module = plugin->GetModule();
    m_plugins.emplace(module, plugin);

    if (!plugin->Main(RED4ext::EMainReason::Load))
    {
        spdlog::warn(L"{} did not initalize properly, unloading...", pluginName);
        Unload(plugin);

        return;
    }

    spdlog::info(L"{} (version: {}, author(s): {}) has been loaded", pluginName, std::to_wstring(pluginVersion),
                 plugin->GetAuthor());
}

PluginSystem::MapIter_t PluginSystem::Unload(std::shared_ptr<PluginBase> aPlugin)
{
    aPlugin->Main(RED4ext::EMainReason::Unload);

    auto module = aPlugin->GetModule();
    auto iter = m_plugins.find(module);
    auto result = m_plugins.erase(iter);

    spdlog::info(L"{} has been unloaded", aPlugin->GetName());
    return result;
}

std::shared_ptr<PluginBase> PluginSystem::CreatePlugin(const std::filesystem::path& aPath,
                                                       wil::unique_hmodule aModule) const
{
    const auto stem = aPath.stem();

    using Supports_t = uint32_t (*)();
    auto supportsFn = reinterpret_cast<Supports_t>(GetProcAddress(aModule.get(), "Supports"));
    if (!supportsFn)
    {
        auto msg = Utils::FormatLastError();
        spdlog::warn(L"Could not retrieve 'Supports' function from '{}'. Error code: {}, msg: '{}', path: '{}'", stem,
                     GetLastError(), msg, aPath);
        return nullptr;
    }

    uint32_t apiVersion;

    try
    {
        apiVersion = supportsFn();
    }
    catch (const std::exception& e)
    {
        spdlog::warn(L"An exception occured while calling 'Supports' function exported by '{}'. Path: '{}'", stem,
                     aPath);
        spdlog::warn(e.what());
        return nullptr;
    }
    catch (...)
    {
        spdlog::warn(L"An unknown exception occured while calling 'Supports' function exported by '{}'. Path: '{}'",
                     stem, aPath);
        return nullptr;
    }

    if (apiVersion < MINIMUM_API_VERSION || apiVersion > LATEST_API_VERSION)
    {
        spdlog::warn(L"'{}' is using an unsupported API version. API version: {}, path: '{}'", stem, apiVersion, aPath);
        return nullptr;
    }

    switch (apiVersion)
    {
    case RED4EXT_API_VERSION_0:
    {
        return std::make_shared<v0::Plugin>(aPath, std::move(aModule));
    }
    }

    return nullptr;
}
