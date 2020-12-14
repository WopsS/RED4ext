#pragma once

#include <Launchers/BaseLauncher.hpp>

namespace REDext::Launchers
{
    class GOGGalaxy : public BaseLauncher
    {
    public:
        GOGGalaxy() = default;
        ~GOGGalaxy() = default;

        const std::wstring GetName() const final;

        const bool IsInstalled() const final;
        const bool IsRunning() const final;

        const bool Launch() const final;

    private:
        BaseLauncher::GameInfo GetGameInfo() final;
    };
}
