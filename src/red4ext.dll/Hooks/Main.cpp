#include "stdafx.hpp"
#include "Hooks/Main.hpp"
#include "App.hpp"
#include "REDhook.hpp"

namespace
{
int64_t Main();
REDhook<decltype(&Main)> Main_h({0x40, 0x53, 0x48, 0x81, 0xEC, 0xC0, 0x01, 0x00, 0x00, 0xFF, 0x15, 0xCC, 0xCC,
                                 0xCC, 0xCC, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC, 0xE8, 0xCC, 0xCC, 0xCC, 0xCC},
                                &Main, 1);

int64_t Main()
{
    auto app = App::Get();

    app->Init();
    auto result = Main_h();
    app->Shutdown();

    return result;
}
} // namespace

void Main::Attach()
{
    Main_h.Attach();
}

void Main::Detach()
{
    Main_h.Detach();
}
