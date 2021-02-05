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
    constexpr auto name = L"RED4ext";

    // Make sure there is a "RED4ext" directory in the "Documents".
    auto [err, docsPath] = GetDocumentsPath();
    if (err)
    {
        MessageBox(nullptr, L"Could not get the path to 'Documents' folder.", name, MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    docsPath /= name;
    if (!std::filesystem::exists(docsPath) && !std::filesystem::create_directories(docsPath))
    {
        return;
    }

#ifdef _DEBUG
    DevConsole::Alloc();
#endif

    // Initialize the logger.
    InitializeLogger(docsPath);

    spdlog::info(L"{} started", name);
    spdlog::debug(L"Base address is {:#x}", reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)));
}

void App::Run()
{
}

void App::Shutdown()
{
    m_pluginManager.Shutdown();
    spdlog::shutdown();

#ifdef _DEBUG
    DevConsole::Free();
#endif
}

PluginManager* App::GetPluginManager()
{
    return &m_pluginManager;
}

std::tuple<std::error_code, std::filesystem::path> App::GetDocumentsPath()
{
    wchar_t* pathRaw = nullptr;
    std::filesystem::path path;

    if (FAILED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, &pathRaw)))
    {
        return {std::error_code(ERROR_PATH_NOT_FOUND, std::system_category()), ""};
    }

    path = pathRaw;
    CoTaskMemFree(pathRaw);

    return {{std::error_code()}, path};
}

void App::InitializeLogger(std::filesystem::path aRoot)
{
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    auto file = std::make_shared<spdlog::sinks::basic_file_sink_st>(aRoot / L"game.log", true);

    spdlog::sinks_init_list sinks = {console, file};

    auto logger = std::make_shared<spdlog::logger>("", sinks);
    spdlog::set_default_logger(logger);

#ifdef _DEBUG
    logger->flush_on(spdlog::level::trace);
    spdlog::set_level(spdlog::level::trace);
#else
    logger->flush_on(spdlog::level::info);
    spdlog::set_level(spdlog::level::info);
#endif
}
