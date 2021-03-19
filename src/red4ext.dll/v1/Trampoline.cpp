#include "stdafx.hpp"
#include "Trampoline.hpp"
#include "App.hpp"

void* v1::Trampoline::Alloc(RED4ext::PluginHandle aHandle)
{
    auto app = App::Get();
    auto pluginsManager = app->GetPluginsManager();

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        auto trampolinesManager = app->GetTrampolinesManager();
        auto memory = trampolinesManager->Alloc(plugin);
        if (memory)
        {
            return memory;
        }
    }

    return nullptr;
}

void v1::Trampoline::Free(RED4ext::PluginHandle aHandle, void* aAddress)
{
    auto app = App::Get();
    auto pluginsManager = app->GetPluginsManager();

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        auto trampolinesManager = app->GetTrampolinesManager();
        trampolinesManager->Free(plugin, aAddress);
    }
}
