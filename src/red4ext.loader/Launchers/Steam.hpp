#pragma once

#include <Launchers/BaseLauncher.hpp>

namespace RED4ext::Launchers
{
    class Steam : public BaseLauncher
    {
    public:
        Steam() = default;
        ~Steam() = default;

        const std::wstring GetName() const final;

        const bool IsInstalled() const final;
        const bool IsRunning() const final;

        const bool Launch() const final;

        std::error_code CreateGame(wchar_t* aCmdLine) final;

    private:
        BaseLauncher::GameInfo GetGameInfo() final;
    };
}
