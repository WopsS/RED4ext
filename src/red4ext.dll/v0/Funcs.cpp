#include "stdafx.hpp"
#include "Funcs.hpp"
#include "App.hpp"
#include "Utils.hpp"

bool v0::AddState(RED4ext::PluginHandle aHandle, RED4ext::EGameStateType aType, RED4ext::GameState* aState)
{
    spdlog::trace("Request to add a game state has been received from plugin with handle {}", fmt::ptr(aHandle));

    if (!aState)
    {
        spdlog::warn("The state's address is NULL");
        return false;
    }

    auto app = App::Get();
    if (!app)
    {
        return false;
    }

    auto pluginSystem = app->GetPluginSystem();
    auto plugin = pluginSystem->GetPlugin(aHandle);
    if (!plugin)
    {
        spdlog::warn("Could not find a plugin with handle {}", fmt::ptr(aHandle));
        return false;
    }

    auto stateSystem = app->GetStateSystem();
    if (stateSystem->Add(plugin, aType, aState->OnEnter, aState->OnUpdate, aState->OnExit))
    {
        spdlog::trace(L"The request to add a '{}' state for '{}' has been successfully completed",
                      Utils::GetStateName(aType), plugin->GetName());
        return true;
    }

    spdlog::warn(L"The request to add a '{}' state for '{}' has failed", Utils::GetStateName(aType), plugin->GetName());
    return false;
}

bool v0::Hooking::Attach(RED4ext::PluginHandle aHandle, void* aTarget, void* aDetour, void** aOriginal)
{
    spdlog::trace("Attach request received from plugin with handle {}", fmt::ptr(aHandle));

    if (aTarget == nullptr || aDetour == nullptr)
    {
        spdlog::warn("One of the required parameters for attaching hook is NULL");
        return false;
    }

    auto app = App::Get();
    if (!app)
    {
        return false;
    }

    auto pluginSystem = app->GetPluginSystem();
    auto plugin = pluginSystem->GetPlugin(aHandle);
    if (!plugin)
    {
        spdlog::warn("Could not find a plugin with handle {}", fmt::ptr(aHandle));
        return false;
    }

    auto hookingSystem = app->GetHookingSystem();
    return hookingSystem->Attach(plugin, aTarget, aDetour, aOriginal);
}

bool v0::Hooking::Detach(RED4ext::PluginHandle aHandle, void* aTarget)
{
    spdlog::trace("Detach request received from plugin with handle {}", fmt::ptr(aHandle));

    if (aTarget == nullptr)
    {
        spdlog::warn("One of the required parameters for detaching hook is NULL");
        return false;
    }

    auto app = App::Get();
    if (!app)
    {
        return false;
    }

    auto pluginSystem = app->GetPluginSystem();
    auto plugin = pluginSystem->GetPlugin(aHandle);
    if (!plugin)
    {
        spdlog::warn("Could not find a plugin with handle {}", fmt::ptr(aHandle));
        return false;
    }

    auto hookingSystem = app->GetHookingSystem();
    return hookingSystem->Detach(plugin, aTarget);
}
