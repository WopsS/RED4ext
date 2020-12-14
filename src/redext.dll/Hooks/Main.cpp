#include <stdafx.hpp>
#include <App.hpp>
#include <Hooks/Main.hpp>
#include <REDs/REDhook.hpp>

namespace
{
    int64_t Main();
    REDext::REDhook<decltype(&Main)> Main_h({ 0x40, 0x53, 0x48, 0x81, 0xEC, 0xC0, 0x01, 0x00, 0x00,
                                              0xFF, 0x15, 0xCC, 0xCC, 0xCC, 0xCC, 0xE8, 0xCC, 0xCC,
                                              0xCC, 0xCC, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC },
                                            &Main, 1);

    int64_t Main()
    {
        auto app = REDext::App::Get();

        app->Init();
        auto result = Main_h();
        app->Shutdown();

        return result;
    }
}

void REDext::Hooks::Main::Attach()
{
    Main_h.Attach();
}

void REDext::Hooks::Main::Detach()
{
    Main_h.Detach();
}
