#pragma once

namespace RED4ext::Launchers
{
    class BaseLauncher
    {
    public:
        BaseLauncher();
        virtual ~BaseLauncher();

        virtual const std::wstring GetName() const = 0;

        virtual const bool IsInstalled() const = 0;
        virtual const bool IsRunning() const = 0;
        virtual const bool Launch() const = 0;

        virtual std::error_code CreateGame(wchar_t* aCmdLine);
        void ResumeGame();
        void TerminateGame();

        std::error_code Inject(const std::wstring_view aModule, const std::string_view aFunction,
                               const std::wstring& aParameter);

    protected:
        struct GameInfo
        {
            std::filesystem::path RootDir;
            std::filesystem::path ExePath;
        };

        virtual GameInfo GetGameInfo() = 0;

    private:
        PROCESS_INFORMATION m_processInfo;
    };
}
