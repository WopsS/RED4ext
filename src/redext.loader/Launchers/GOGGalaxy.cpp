#include <stdafx.hpp>
#include <Launchers/GOGGalaxy.hpp>
#include <Registry.hpp>

namespace
{
    constexpr auto GAME_ID = L"1423049311";
}

const std::wstring REDext::Launchers::GOGGalaxy::GetName() const
{
    return L"GOG Galaxy";
}

const bool REDext::Launchers::GOGGalaxy::IsInstalled() const
{
    return !Registry::Read<std::wstring>(Registry::Key::LocalMachine, L"SOFTWARE", L"WOW6432Node", L"GOG.com",
                                         L"GalaxyClient", L"paths", L"client")
              .empty();
}

const bool REDext::Launchers::GOGGalaxy::IsRunning() const
{
    // Since we can't make GOG Galaxy track the time when the game is started outside of the application, we are going
    // to always return true here.
    return true;
}

const bool REDext::Launchers::GOGGalaxy::Launch() const
{
    // See "IsRunning" method.
    return false;
}

REDext::Launchers::BaseLauncher::GameInfo REDext::Launchers::GOGGalaxy::GetGameInfo()
{
    BaseLauncher::GameInfo info;
    info.ExePath = Registry::Read<std::wstring>(Registry::Key::LocalMachine, L"SOFTWARE", L"WOW6432Node", L"GOG.com",
                                                L"Games", GAME_ID, L"exe");

    info.RootDir = info.ExePath.parent_path();
    return info;
}
