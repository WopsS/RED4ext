#include <stdafx.hpp>
#include <DevConsole.hpp>

void REDext::DevConsole::Alloc()
{
    if (AllocConsole())
    {
        freopen("CONOUT$", "w", stdout);
        SetConsoleTitle(L"REDext Console");
    }
    else
    {
        auto message = fmt::format(L"Could not allocate the debug console, error {:#x}.", GetLastError());
        MessageBox(nullptr, message.c_str(), L"REDext", MB_OK | MB_ICONERROR);
    }
}

void REDext::DevConsole::Free()
{
    if (!FreeConsole())
    {
        auto message = fmt::format(L"Could not free the debug console, error {:#x}", GetLastError());
        MessageBox(nullptr, message.c_str(), L"REDext", MB_OK | MB_ICONERROR);
    }
}
