#include "stdafx.hpp"
#include "Hooking.hpp"
#include "App.hpp"
#include "PluginsManager.hpp"
#include "HookingManager.hpp"

void v0::Hooking::Create(RED4ext::PluginHandle aHandle, void* aTarget, void* aDetour, void** aOriginal)
{
    auto app = App::Get();
    //auto pluginsManager = app->GetPluginsManager();
    PluginsManager* pluginsManager;

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        //auto hookingManager = app->GetHookingManager();
        HookingManager* hookingManager;
        hookingManager->Create(plugin, aTarget, aDetour, aOriginal);
    }
}

void v0::Hooking::Remove(RED4ext::PluginHandle aHandle, void* aTarget)
{
    auto app = App::Get();
    // auto pluginsManager = app->GetPluginsManager();
    PluginsManager* pluginsManager;

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        // auto hookingManager = app->GetHookingManager();
        HookingManager* hookingManager;
        hookingManager->Remove(plugin, aTarget);
    }
}

bool v0::Hooking::Attach(RED4ext::PluginHandle aHandle, void* aTarget)
{
    auto app = App::Get();
    // auto pluginsManager = app->GetPluginsManager();
    PluginsManager* pluginsManager;

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        // auto hookingManager = app->GetHookingManager();
        HookingManager* hookingManager;
        return hookingManager->Attach(plugin, aTarget);
    }

    return false;
}

bool v0::Hooking::Detach(RED4ext::PluginHandle aHandle, void* aTarget)
{
    auto app = App::Get();
    // auto pluginsManager = app->GetPluginsManager();
    PluginsManager* pluginsManager;

    auto plugin = pluginsManager->GetPlugin(aHandle);
    if (plugin)
    {
        // auto hookingManager = app->GetHookingManager();
        HookingManager* hookingManager;
        return hookingManager->Detach(plugin, aTarget);
    }

    return false;
}

void* v0::Hooking::FindPattern(uint8_t* aPattern, size_t aPatternSize, uint8_t aWildcard, size_t aExpectedMatches,
                               size_t aIndex)
{
    assert(aIndex < aExpectedMatches);

    //auto patterns = Patterns::Get();
    //auto address = patterns->Find(aPattern, aPatternSize, aExpectedMatches, aIndex, aWildcard, false);
    //return reinterpret_cast<void*>(address);

    return nullptr;
}
