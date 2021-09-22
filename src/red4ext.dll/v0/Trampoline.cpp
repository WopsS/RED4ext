#include "stdafx.hpp"
#include "Trampoline.hpp"
#include "App.hpp"
#include "PluginsManager.hpp"
#include "TrampolinesManager.hpp"

void* v0::Trampoline::Alloc(RED4ext::PluginHandle aHandle)
{
    auto app = App::Get();
    //auto pluginsManager = app->GetPluginsManager();
    PluginsManager* pluginsManager;

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        //auto trampolinesManager = app->GetTrampolinesManager();
        TrampolinesManager* trampolinesManager;

        auto memory = trampolinesManager->Alloc(plugin);
        if (memory)
        {
            return memory;
        }
    }

    return nullptr;
}

void v0::Trampoline::Free(RED4ext::PluginHandle aHandle, void* aAddress)
{
    auto app = App::Get();
    //auto pluginsManager = app->GetPluginsManager();
    PluginsManager* pluginsManager;

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        //auto trampolinesManager = app->GetTrampolinesManager();
        TrampolinesManager* trampolinesManager;
        trampolinesManager->Free(plugin, aAddress);
    }
}
