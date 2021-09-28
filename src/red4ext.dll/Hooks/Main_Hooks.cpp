#include "stdafx.hpp"
#include "Main_Hooks.hpp"
#include "Addresses.hpp"
#include "App.hpp"
#include "Hook.hpp"

namespace
{
bool isAttached = false;

int32_t _Main();
Hook<decltype(&_Main)> Main_fnc(Addresses::Global_Main, &_Main);

int32_t _Main()
{
    auto app = App::Get();
    app->Startup();

    auto result = Main_fnc();

    app->Shutdown();
    return result;
}
} // namespace

bool Hooks::Main::Attach()
{
    spdlog::trace("Trying to attach the hook for the main function...");

    auto result = Main_fnc.Attach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not attach the hook for the main function. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the main function was attached");
    }

    isAttached = result == NO_ERROR;
    return isAttached;
}

bool Hooks::Main::Detach()
{
    if (!isAttached)
    {
        return false;
    }

    spdlog::trace("Trying to detach the hook for the main function...");

    auto result = Main_fnc.Detach();
    if (result != NO_ERROR)
    {
        spdlog::error("Could not detach the hook for the main function. Detour error code: {}", result);
    }
    else
    {
        spdlog::trace("The hook for the main function was detached");
    }

    isAttached = result != NO_ERROR;
    return isAttached;
}
