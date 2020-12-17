#include <stdafx.hpp>
#include <App.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <Launchers/CustomLauncher.hpp>
#include <Launchers/GOGGalaxy.hpp>
#include <Launchers/Steam.hpp>
#include <Registry.hpp>

namespace
{
    constexpr auto Name = L"RED4ext";
}

std::error_code RED4ext::App::Init()
{
    // Make sure there is a "RED4ext" directory in the "Documents".
    auto [err, path] = GetDocumentsPath();
    if (err)
    {
        MessageBox(nullptr, L"Could not get the path to 'Documents' folder.", Name, MB_ICONEXCLAMATION | MB_OK);
        return err;
    }

    path /= Name;
    if (!std::filesystem::exists(path) && !std::filesystem::create_directories(path, err))
    {
        return err;
    }

    // Initialize the logger.
    InitializeLogger(path);

    spdlog::info(L"{} loader started", Name);
    return {};
}

std::error_code RED4ext::App::Run(wchar_t* aCmdLine)
{
    spdlog::info(L"Detecting launcher...");

    using namespace RED4ext::Launchers;

    m_launcher.reset(new GOGGalaxy());
    if (!m_launcher->IsInstalled())
    {
        m_launcher.reset(new Steam());
        if (!m_launcher->IsInstalled())
        {
            // We don't have any option, ask the user to choose a directory.
            spdlog::warn("No real launcher found, creating custom one...");
            m_launcher.reset(new CustomLauncher());
        }
    }

    if (m_launcher)
    {
        spdlog::info(L"Found '{}' installed", m_launcher->GetName());
    }
    else
    {
        spdlog::warn(L"No launcher found");
    }

    if (!m_launcher->IsRunning())
    {
        spdlog::info(L"{} is not running, launching...", m_launcher->GetName());

        // We don't reall care if the launcher is started or not, so we won't throw an error.
        if (m_launcher->Launch())
        {
            spdlog::info(L"{} launched", m_launcher->GetName());
        }
    }
    else
    {
        spdlog::info(L"{} is already running, no action needed", m_launcher->GetName());
    }

    spdlog::info(L"Creating the game process");

    auto err = m_launcher->CreateGame(aCmdLine);
    if (err)
    {
        return err;
    }

    spdlog::info(L"The game was process created with success");

    spdlog::info(L"Injecting the DLL");

    std::filesystem::path currDir;
    {
        wchar_t pathPtr[MAX_PATH];
        GetModuleFileName(nullptr, pathPtr, MAX_PATH);

        currDir = pathPtr;
        currDir = currDir.parent_path();
    }

    auto dll = currDir / fmt::format(L"{}.dll", Name);
    err = m_launcher->Inject(L"kernel32.dll", "LoadLibraryW", dll.c_str());
    if (err)
    {
        m_launcher->TerminateGame();
        return err;
    }

    spdlog::info(L"The DLL was injected with success");

    m_launcher->ResumeGame();
    return {};
}

std::error_code RED4ext::App::Shutdown()
{
    spdlog::info(L"Shutting down...");

    // Launcher should free the resources used to start the game.
    m_launcher.reset(nullptr);

    spdlog::info(L"Shutdown complete");
    spdlog::shutdown();

    return {};
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
    auto file = std::make_shared<spdlog::sinks::basic_file_sink_st>(aRoot / L"launcher.log", true);

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
