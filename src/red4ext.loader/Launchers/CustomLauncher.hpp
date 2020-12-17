#pragma once

#include <Launchers/BaseLauncher.hpp>

namespace RED4ext::Launchers
{
    class CustomLauncher : public BaseLauncher
    {
    public:
        CustomLauncher();
        ~CustomLauncher() = default;

        const std::wstring GetName() const final;

        const bool IsInstalled() const final;
        const bool IsRunning() const final;

        const bool Launch() const final;

    private:
        BaseLauncher::GameInfo GetGameInfo() final;
        std::filesystem::path GetGamePath();
    };
}
