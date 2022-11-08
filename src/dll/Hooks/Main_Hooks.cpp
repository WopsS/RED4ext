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
    try
    {
        auto app = App::Get();
        app->Startup();
    }
    catch (const std::exception& e)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An exception occured while RED4ext was starting up.\n\n{}",
                                            Utils::Widen(e.what()));
    }
    catch (...)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An unknown exception occured while RED4ext was starting up.");
    }

    auto result = Main_fnc();

    try
    {
        auto app = App::Get();
        app->Shutdown();
    }
    catch (const std::exception& e)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An exception occured while RED4ext was shutting down.\n\n{}",
                                            Utils::Widen(e.what()));
    }
    catch (...)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE("An unknown exception occured while RED4ext was shutting down.");
    }

    return result;
}
} // namespace

bool Hooks::Main::Attach()
{
    spdlog::trace("Trying to attach the hook for the main function at {}...",
                  RED4EXT_OFFSET_TO_ADDR(Addresses::Global_Main));

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

    spdlog::trace("Trying to detach the hook for the main function at {}...", RED4EXT_OFFSET_TO_ADDR(Addresses::Global_Main));

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
    return !isAttached;
}
