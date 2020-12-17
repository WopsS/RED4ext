#include <stdafx.hpp>
#include <Launchers/BaseLauncher.hpp>

RED4ext::Launchers::BaseLauncher::BaseLauncher()
    : m_processInfo{ 0 }
{
}

RED4ext::Launchers::BaseLauncher::~BaseLauncher()
{
    if (m_processInfo.hThread)
    {
        CloseHandle(m_processInfo.hThread);
    }

    if (m_processInfo.hProcess)
    {
        CloseHandle(m_processInfo.hProcess);
    }
}

std::error_code RED4ext::Launchers::BaseLauncher::CreateGame(wchar_t* aCmdLine)
{
    auto info = GetGameInfo();

    if (!std::filesystem::exists(info.RootDir))
    {
        spdlog::error(L"The game directory '{}' does not exists", info.RootDir.wstring());
        return std::error_code(ERROR_NOT_FOUND, std::system_category());
    }

    if (!std::filesystem::exists(info.ExePath))
    {
        spdlog::error(L"The exe '{}' does not exists", info.ExePath.wstring());
        return std::error_code(ERROR_NOT_FOUND, std::system_category());
    }

    STARTUPINFO startupInfo = { 0 };
    if (!CreateProcess(info.ExePath.c_str(), aCmdLine, nullptr, nullptr, false, CREATE_SUSPENDED, nullptr,
                       info.RootDir.c_str(), &startupInfo, &m_processInfo))
    {
        spdlog::error(L"The game process could not be created, error {:#x}", GetLastError());
        return std::error_code(GetLastError(), std::system_category());
    }

    return std::error_code();
}

void RED4ext::Launchers::BaseLauncher::ResumeGame()
{
    ResumeThread(m_processInfo.hThread);
}

void RED4ext::Launchers::BaseLauncher::TerminateGame()
{
    TerminateProcess(m_processInfo.hProcess, 1);
}

std::error_code RED4ext::Launchers::BaseLauncher::Inject(const std::wstring_view aModule,
                                                        const std::string_view aFunction,
                                                        const std::wstring& aParameter)
{
    auto module = GetModuleHandle(aModule.data());
    if (!module)
    {
        spdlog::error(L"Could not get '{}' module", aModule);
        return std::error_code(GetLastError(), std::system_category());
    }

    auto funcAddr = GetProcAddress(module, aFunction.data());
    if (!funcAddr)
    {
        size_t length =
          MultiByteToWideChar(CP_UTF8, 0, aFunction.data(), static_cast<int32_t>(aFunction.length()), 0, 0);

        std::wstring wideFunc;
        wideFunc.resize(length);

        MultiByteToWideChar(CP_UTF8, 0, aFunction.data(), static_cast<int32_t>(aFunction.length()), &wideFunc[0],
                            static_cast<int32_t>(wideFunc.length()));

        spdlog::error(L"Could not get the address for function '{}' from '{}'", wideFunc, aModule);
        return std::error_code(GetLastError(), std::system_category());
    }

    auto bytesToWrite = (aParameter.size() + 1) * sizeof(std::wstring::value_type);

    auto baseAddress = VirtualAllocEx(m_processInfo.hProcess, nullptr, bytesToWrite, MEM_COMMIT, PAGE_READWRITE);
    if (!baseAddress)
    {
        spdlog::error(L"Could not allocate {} bytes in the game process", bytesToWrite);
        return std::error_code(GetLastError(), std::system_category());
    }

    size_t bytesWritten = 0;
    if (!WriteProcessMemory(m_processInfo.hProcess, baseAddress, aParameter.c_str(), bytesToWrite,
                            reinterpret_cast<SIZE_T*>(&bytesWritten)))
    {
        spdlog::error(L"Could not write {} bytes in the game process", bytesToWrite);
        return std::error_code(GetLastError(), std::system_category());
    }

    if (bytesWritten != bytesToWrite)
    {
        spdlog::error(L"Could not write {} bytes in the game process, only {} bytes written", bytesToWrite,
                      bytesWritten);
        return std::error_code(GetLastError(), std::system_category());
    }

    auto thread = CreateRemoteThread(m_processInfo.hProcess, nullptr, 0,
                                     reinterpret_cast<LPTHREAD_START_ROUTINE>(funcAddr), baseAddress, 0, nullptr);
    if (!thread)
    {
        spdlog::error(L"Could not create a thread in the game process");
        return std::error_code(GetLastError(), std::system_category());
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    VirtualFreeEx(m_processInfo.hProcess, baseAddress, 0, MEM_RELEASE);
    return std::error_code();
}
