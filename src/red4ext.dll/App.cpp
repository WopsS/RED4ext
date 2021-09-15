#include "stdafx.hpp"
#include "App.hpp"
#include "DevConsole.hpp"
#include "Utils.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::unique_ptr<App> App::m_instance;

App::App()
    : m_pluginsManager(&m_hookingManager, &m_trampolinesManager)
{
}

void App::Construct()
{
    static std::once_flag flag;
    std::call_once(flag, []() { m_instance.reset(new App()); });
}

App* App::Get()
{
    return m_instance.get();
}

void App::Init()
{
#ifdef _DEBUG
    DevConsole::Alloc();
#endif

    CreateLogger();

    spdlog::info("RED4ext started");
    spdlog::debug("Base address is {:#x}", reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)));
}

void App::Shutdown()
{
    spdlog::shutdown();

#ifdef _DEBUG
    DevConsole::Free();
#endif
}

HookingManager* App::GetHookingManager()
{
    return &m_hookingManager;
}

TrampolinesManager* App::GetTrampolinesManager()
{
    return &m_trampolinesManager;
}

PluginsManager* App::GetPluginsManager()
{
    return &m_pluginsManager;
}

std::filesystem::path App::GetRootDirectory()
{
    constexpr auto pathLength = MAX_PATH + 1;

    // Try to get the executable path until we can fit the length of the path.
    std::wstring filename;
    do
    {
        filename.resize(filename.size() + pathLength, '\0');

        auto length = GetModuleFileName(nullptr, filename.data(), static_cast<uint32_t>(filename.size()));
        if (length > 0)
        {
            // Resize it to the real, std::filesystem::path" will use the string's length instead of recounting it.
            filename.resize(length);
        }
    } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);

    auto gameRoot = std::filesystem::path(filename)
                        .parent_path()  // Resolve to "x64" directory.
                        .parent_path()  // Resolve to "bin" directory.
                        .parent_path(); // Resolve to game root directory.

    return gameRoot / L"red4ext";
}

std::filesystem::path App::GetPluginsDirectory()
{
    return GetRootDirectory() / "plugins";
}

std::filesystem::path App::GetLogsDirectory()
{
    return GetRootDirectory() / "logs";
}

std::filesystem::path App::GetExecutablePath()
{
    constexpr auto pathLength = MAX_PATH + 1;

    // Try to get the executable path until we can fit the length of the path.
    std::wstring filename;
    do
    {
        filename.resize(filename.size() + pathLength, '\0');

        auto length = GetModuleFileName(nullptr, filename.data(), static_cast<uint32_t>(filename.size()));
        if (length > 0)
        {
            // Resize it to the real, std::filesystem::path" will use the string's length instead of recounting it.
            filename.resize(length);
        }
    } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);

    return filename;
}

void App::CreateLogger()
{
    std::error_code errCode;
    auto logsPath = GetLogsDirectory();
    if (!std::filesystem::exists(logsPath, errCode) && !std::filesystem::create_directories(logsPath, errCode))
    {
        auto err = GetLastError();
        auto message = fmt::format(L"{}\nCould not create '{}' directory, last error 0x{:X}, error code {}.",
                                   Utils::FormatErrorMessage(err), logsPath.c_str(), err, errCode.value());
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONERROR | MB_OK);
        return;
    }

    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logsPath / "game.log", true);

    spdlog::sinks_init_list sinks = {console, file};

    auto logger = std::make_shared<spdlog::logger>("", sinks);
    spdlog::set_default_logger(logger);

    // Setting the flush on every log, game might crash and spdlog won't flush the buffer.
#ifdef _DEBUG
    logger->flush_on(spdlog::level::trace);
    spdlog::set_level(spdlog::level::trace);
#else
    logger->flush_on(spdlog::level::info);
    spdlog::set_level(spdlog::level::info);
#endif
}
