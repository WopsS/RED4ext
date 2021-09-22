#include "stdafx.hpp"
#include "DevConsole.hpp"
#include "Utils.hpp"

DevConsole::DevConsole(const Config& aConfig)
    : m_isCreated(false)
    , m_isRedirected(false)
{
    if (aConfig.HasDevConsole())
    {
        if (AllocConsole())
        {
            m_isCreated = true;

            SetConsoleTitle(L"RED4ext Console");

            // Disable the close button / context menu.
            auto console = GetConsoleWindow();
            if (console)
            {
                auto menu = GetSystemMenu(console, false);
                if (menu)
                {
                    DeleteMenu(menu, SC_CLOSE, MF_BYCOMMAND);
                }
            }

            // Now redirect the output.
            if (!freopen("CONOUT$", "w", stdout))
            {
                SHOW_MESSAGE_BOX_FILE_LINE(MB_ICONWARNING | MB_OK,
                                           L"Could not redirect the standard output to console.");
            }
            else
            {
                m_isRedirected = true;

                // This is not mandatory to be open, but is nice to have.
                if (!freopen("CONOUT$", "w", stderr))
                {
                    SHOW_MESSAGE_BOX_FILE_LINE(MB_ICONWARNING | MB_OK,
                                               L"Could not redirect the standard error output to console.");
                }
            }
        }
        else
        {
            SHOW_LAST_ERROR_MESSAGE_FILE_LINE(L"Could not create the development console.");
        }
    }
}

DevConsole::~DevConsole()
{
    if (m_isCreated)
    {
        FreeConsole();
    }
}

bool DevConsole::IsOutputRedirected() const
{
    return m_isRedirected;
}
