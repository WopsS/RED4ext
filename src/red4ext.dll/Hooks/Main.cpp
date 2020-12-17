#include <stdafx.hpp>
#include <Hooks/Main.hpp>

#include <App.hpp>
#include <REDs/REDhook.hpp>

namespace
{
    HMODULE dllModule;

    int64_t Main();
    RED4ext::REDhook<decltype(&Main)> Main_h({ 0x40, 0x53, 0x48, 0x81, 0xEC, 0xC0, 0x01, 0x00, 0x00,
                                               0xFF, 0x15, 0xCC, 0xCC, 0xCC, 0xCC, 0xE8, 0xCC, 0xCC,
                                               0xCC, 0xCC, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC },
                                             &Main, 1);

    int64_t Main()
    {
        auto app = RED4ext::App::Get();

        app->Init(dllModule);
        auto result = Main_h();
        app->Shutdown();

        return result;
    }
}

void RED4ext::Hooks::Main::Attach(HMODULE aModule)
{
    Main_h.Attach();
    dllModule = aModule;
}

void RED4ext::Hooks::Main::Detach()
{
    Main_h.Detach();
}
