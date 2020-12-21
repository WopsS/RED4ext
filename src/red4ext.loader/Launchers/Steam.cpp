#include <stdafx.hpp>
#include <Launchers/Steam.hpp>
#include <Registry.hpp>

namespace
{
    constexpr auto GAME_ID = L"1091500";
}

const std::wstring RED4ext::Launchers::Steam::GetName() const
{
    return L"Steam";
}

const bool RED4ext::Launchers::Steam::IsInstalled() const
{
    return !Registry::Read<std::wstring>(Registry::Key::LocalMachine, L"SOFTWARE", L"WOW6432Node", L"Valve", L"Steam",
                                         L"InstallPath")
              .empty();
}

const bool RED4ext::Launchers::Steam::IsRunning() const
{
    return Registry::Read<uint32_t>(Registry::Key::CurrentUser, L"SOFTWARE", L"Valve", L"Steam", L"ActiveProcess",
                                    L"pid") > 0;
}

const bool RED4ext::Launchers::Steam::Launch() const
{
    std::filesystem::path installPath =
      Registry::Read<std::wstring>(Registry::Key::CurrentUser, L"SOFTWARE", L"Valve", L"Steam", L"SteamPath");

    std::filesystem::path exePath =
      Registry::Read<std::wstring>(Registry::Key::CurrentUser, L"SOFTWARE", L"Valve", L"Steam", L"SteamExe");

    STARTUPINFO startupInfo = { 0 };
    PROCESS_INFORMATION processInfo = { 0 };

    if (!CreateProcess(exePath.c_str(), nullptr, nullptr, nullptr, false, 0, nullptr, installPath.c_str(), &startupInfo,
                       &processInfo))
    {
        spdlog::error(L"{} could not be started, error {:#x}", GetName(), GetLastError());
        return false;
    }

    do
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
    } while (!IsRunning());

    CloseHandle(processInfo.hThread);
    CloseHandle(processInfo.hProcess);

    return true;
}

std::error_code RED4ext::Launchers::Steam::CreateGame(wchar_t* aCmdLine)
{
    if (IsRunning())
    {
        SetEnvironmentVariable(L"SteamAppId", GAME_ID);
        SetEnvironmentVariable(L"SteamGameId", GAME_ID);
    }

    return BaseLauncher::CreateGame(aCmdLine);
}

RED4ext::Launchers::BaseLauncher::GameInfo RED4ext::Launchers::Steam::GetGameInfo()
{
    BaseLauncher::GameInfo info;
    info.RootDir = Registry::Read<std::wstring>(Registry::Key::LocalMachine, L"SOFTWARE", L"Microsoft", L"Windows",
                                                L"CurrentVersion", L"Uninstall", fmt::format(L"Steam App {}", GAME_ID),
                                                L"InstallLocation");

    info.RootDir = info.RootDir / L"bin" / L"x64";
    info.ExePath = info.RootDir / "Cyberpunk2077.exe";
    return info;
}
