#include <stdafx.hpp>
#include <Hooks/Main.hpp>

#include <App.hpp>
#include <REDs/REDhook.hpp>

namespace
{
    HMODULE dllModule;

    int64_t Main();
    REDext::REDhook<decltype(&Main)> Main_h({ 0x40, 0x53, 0x48, 0x81, 0xEC, 0xC0, 0x01, 0x00, 0x00,
                                              0xFF, 0x15, 0xCC, 0xCC, 0xCC, 0xCC, 0xE8, 0xCC, 0xCC,
                                              0xCC, 0xCC, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC },
                                            &Main, 1);

    int64_t Main()
    {
        auto app = REDext::App::Get();

        app->Init(dllModule);
        auto result = Main_h();
        app->Shutdown();

        return result;
    }
}

void REDext::Hooks::Main::Attach(HMODULE aModule)
{
    Main_h.Attach();
    dllModule = aModule;
}

void REDext::Hooks::Main::Detach()
{
    Main_h.Detach();
}
