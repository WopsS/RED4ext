#include "stdafx.hpp"
#include "Hooks/CInitializationState.hpp"
#include "App.hpp"
#include "Patterns.hpp"
#include "REDhook.hpp"

#include <RED4ext/GameApplication.hpp>
#include <RED4ext/GameStates.hpp>

namespace
{
bool _CInitializationState_Run(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp);
REDhook<decltype(&_CInitializationState_Run)> CInitializationState_Run;

bool _CInitializationState_Run(RED4ext::CInitializationState* aThis, RED4ext::CGameApplication* aApp)
{
    auto result = CInitializationState_Run(aThis, aApp);

    /*
     * This is called multiple times, maybe it is doing some internal initalization while showing the intro. It returns
     * true when the state is finished and it should call `Done`, false if it is not and will be run again.
     *
     * The engine is doing some game checks to see if it should set the state to "CRunningState" or not. We are going to
     * copy this behavior here, but not as the game does it.
     */
    auto nextState = aApp->nextState;
    if (result && nextState)
    {
        auto name = nextState->GetName();
        if (strcmp(name, "Running") == 0)
        {
            auto app = App::Get();
            auto pluginsDir = app->GetPluginsDirectory();

            auto pluginsManager = app->GetPluginsManager();
            pluginsManager->LoadAll(pluginsDir);
        }
    }

    return result;
}
} // namespace

void CInitializationState::Attach()
{
    new (&CInitializationState_Run)
        REDhook<decltype(&_CInitializationState_Run)>({0x48, 0x83, 0xEC, 0x28, 0x48, 0x8B, 0x05, 0xCC, 0xCC, 0xCC,
                                                       0xCC, 0x4C, 0x8B, 0xC2, 0x8B, 0x88, 0xF8, 0x00, 0x00, 0x00},
                                                      &_CInitializationState_Run, 1);

    //CInitializationState_Run.attach();
}

void CInitializationState::Detach()
{
    //CInitializationState_Run.detach();
}
