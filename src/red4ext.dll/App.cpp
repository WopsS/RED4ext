#include "stdafx.hpp"
#include "App.hpp"
#include "DevConsole.hpp"
#include "Utils.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

std::unique_ptr<App> App::m_instance;

App::App(HMODULE aModule)
    : m_module(aModule)
{
}

void App::Construct(HMODULE aModule)
{
    static std::once_flag flag;
    std::call_once(flag, [aModule]() {
        if (!m_instance)
        {
            m_instance.reset(new App(aModule));
        }
    });
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

    spdlog::info(L"RED4ext started");
    spdlog::debug(L"Base address is {:#x}", reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)));
}

void App::Shutdown()
{
    spdlog::shutdown();

#ifdef _DEBUG
    DevConsole::Free();
#endif
}

PluginManager* App::GetPluginManager()
{
    return &m_pluginManager;
}

std::filesystem::path App::GetRootDirectory()
{
    constexpr auto pathLength = MAX_PATH + 1;

    // Try to get the executable path until we can fit the length of the path.
    std::wstring filename;
    do
    {
        filename.resize(filename.size() + pathLength, '\0');

        auto length = GetModuleFileName(m_module, filename.data(), static_cast<uint32_t>(filename.size()));
        if (length > 0)
        {
            // Resize it to the real, std::filesystem::path" will use the string's length instead of recounting it.
            filename.resize(length);
        }
    } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);

    return std::filesystem::path(filename).parent_path();
}

std::filesystem::path App::GetPluginsDirectory()
{
    return GetRootDirectory() / L"plugins";
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
    auto logsPath = GetRootDirectory() / L"logs";
    if (!std::filesystem::exists(logsPath) && !std::filesystem::create_directories(logsPath))
    {
        auto err = GetLastError();
        auto message = fmt::format(L"{}\nCould not create '{}' directory, error 0x{:X}.",
                                   Utils::FormatErrorMessage(err), logsPath.c_str(), err);
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_ICONERROR | MB_OK);
        return;
    }

    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    auto file = std::make_shared<spdlog::sinks::basic_file_sink_st>(logsPath / L"game.log", true);

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
