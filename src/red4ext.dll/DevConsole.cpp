#include "stdafx.hpp"
#include "DevConsole.hpp"

void DevConsole::Alloc()
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

void DevConsole::Free()
{
    if (!FreeConsole())
    {
        auto message = fmt::format(L"Could not free the debug console, error {:#x}", GetLastError());
        MessageBox(nullptr, message.c_str(), L"RED4ext", MB_OK | MB_ICONERROR);
    }
}
