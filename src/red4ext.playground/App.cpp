#include "stdafx.hpp"
#include "App.hpp"

RED4ext::Playground::App* RED4ext::Playground::App::Get()
{
    static App app;
    return &app;
}

void RED4ext::Playground::App::Init()
{
    // Make sure there is a "RED4ext" directory in the "Documents".
    auto [err, docsPath] = GetDocumentsPath();
    if (err)
    {
        MessageBox(nullptr, L"Could not get the path to 'Documents' folder.", L"RED4ext", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    if (!std::filesystem::exists(docsPath) && !std::filesystem::create_directories(docsPath))
    {
        return;
    }

    // Initialize the logger.
    InitializeLogger(docsPath);
}

void RED4ext::Playground::App::Run()
{
}

void RED4ext::Playground::App::Shutdown()
{
    spdlog::shutdown();
}

std::tuple<std::error_code, std::filesystem::path> RED4ext::Playground::App::GetDocumentsPath() const
{
    wchar_t* pathRaw = nullptr;
    std::filesystem::path path;

    if (FAILED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, &pathRaw)))
    {
        return { std::error_code(ERROR_PATH_NOT_FOUND, std::system_category()), "" };
    }

    path = pathRaw;
    CoTaskMemFree(pathRaw);

    return { { std::error_code() }, path / L"RED4ext" };
}

void RED4ext::Playground::App::InitializeLogger(std::filesystem::path aRoot)
{
    auto console = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
    auto file = std::make_shared<spdlog::sinks::basic_file_sink_st>(aRoot / L"playground.log", true);

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
