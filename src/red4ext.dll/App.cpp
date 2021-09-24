#include "stdafx.hpp"
#include "App.hpp"
#include "Image.hpp"
#include "Utils.hpp"
#include "Version.hpp"

namespace
{
std::unique_ptr<App> g_app;
}

App::App()
    : m_config(m_paths)
    , m_devConsole(m_config)
{
    Utils::CreateLogger(m_paths, m_config, m_devConsole);

    spdlog::info("RED4ext ({}) is initializing...", RED4EXT_GIT_TAG);

    spdlog::info("Using the following paths:");
    spdlog::info(L"  Root: {}", m_paths.GetRootDir());
    spdlog::info(L"  RED4ext: {}", m_paths.GetRED4extDir());
    spdlog::info(L"  Logs: {}", m_paths.GetLogsDir());
    spdlog::info(L"  Config: {}", m_paths.GetConfigFile());

    const auto image = Image::Get();
    const auto& ver = image->GetVersion();
    spdlog::info("Game version is {}.{}{}", ver.major, ver.minor, ver.patch);

    if (!image->IsSupported())
    {
        spdlog::error("This game version ({}.{}{}) is not supported.", ver.major, ver.minor, ver.patch);

        const auto supportedVer = image->GetSupportedVersion();
        fmt::memory_buffer out;
        fmt::format_to(std::back_inserter(out), "The current version of the mod supports only version {}.{}{}, ",
                       supportedVer.major, supportedVer.minor, supportedVer.patch);

        if (ver < supportedVer)
        {
            fmt::format_to(std::back_inserter(out), "try downgrading the mod or updating the game.");
        }
        else
        {
            fmt::format_to(std::back_inserter(out), "try updating the mod or downgrading the game.");
        }

        spdlog::error(fmt::to_string(out));
        return;
    }
}

void App::Construct()
{
    g_app.reset(new App());
}

void App::Destruct()
{
    g_app.reset(nullptr);
    spdlog::shutdown();
}

App* App::Get()
{
    return g_app.get();
}

void App::Init()
{
}

void App::Shutdown()
{
}
