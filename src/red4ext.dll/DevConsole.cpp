#include <stdafx.hpp>
#include <DevConsole.hpp>

void RED4ext::DevConsole::Alloc()
{
    if (AllocConsole())
    {
        freopen("CONOUT$", "w", stdout);
        SetConsoleTitle(L"RED4ext Console");
    }
    else
    {
        auto message = fmt::format(L"Could not allocate the debug console, error {:#x}.", GetLastError());
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_OK | MB_ICONERROR);
    }
}

void RED4ext::DevConsole::Free()
{
    if (!FreeConsole())
    {
        auto message = fmt::format(L"Could not free the debug console, error {:#x}", GetLastError());
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_OK | MB_ICONERROR);
    }
}
