#include <stdafx.hpp>
#include <App.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <DevConsole.hpp>

RED4ext::App* RED4ext::App::Get()
{
    static App app;
    return &app;
}

void RED4ext::App::Init(HMODULE aModule)
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

    m_pluginManager.Init(aModule, docsPath);
}

void RED4ext::App::Run()
{
}

void RED4ext::App::Shutdown()
{
    m_pluginManager.Shutdown();
    spdlog::shutdown();

#ifdef _DEBUG
    DevConsole::Free();
#endif
}

RED4ext::PluginManager* RED4ext::App::GetPluginManager()
{
    return &m_pluginManager;
}

std::tuple<std::error_code, std::filesystem::path> RED4ext::App::GetDocumentsPath()
{
    wchar_t* pathRaw = nullptr;
    std::filesystem::path path;

    if (FAILED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, &pathRaw)))
    {
        return { std::error_code(ERROR_PATH_NOT_FOUND, std::system_category()), "" };
    }

    path = pathRaw;
    CoTaskMemFree(pathRaw);

    return { { std::error_code() }, path };
}

void RED4ext::App::InitializeLogger(std::filesystem::path aRoot)
{
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    auto file = std::make_shared<spdlog::sinks::basic_file_sink_st>(aRoot / L"game.log", true);

    spdlog::sinks_init_list sinks = { console, file };

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
