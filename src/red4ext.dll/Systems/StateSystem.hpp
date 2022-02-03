#pragma once

#include "ISystem.hpp"
#include "PluginBase.hpp"

class StateSystem : public ISystem
{
public:
    using Func_t = bool (*)(RED4ext::CGameApplication*);

    ESystemType GetType() final;

    void Startup() final;
    void Shutdown() final;

    bool Add(std::shared_ptr<PluginBase> aPlugin, RED4ext::EGameStateType aStateType, Func_t aOnEnter, Func_t aOnUpdate,
             Func_t aOnExit);

    bool OnEnter(RED4ext::EGameStateType aStateType, RED4ext::CGameApplication* aApp);
    bool OnUpdate(RED4ext::EGameStateType aStateType, RED4ext::CGameApplication* aApp);
    bool OnExit(RED4ext::EGameStateType aStateType, RED4ext::CGameApplication* aApp);

private:
    struct StateItem
    {
        std::shared_ptr<PluginBase> plugin;
        Func_t func;
    };

    struct State
    {
        std::list<StateItem> onEnter;
        std::list<StateItem> onUpdate;
        std::list<StateItem> onExit;
    };

    State* GetStateByType(RED4ext::EGameStateType aStateType);

    bool Run(std::wstring_view aAction, std::list<StateItem>& aList, RED4ext::CGameApplication* aApp);

    State m_baseInitialization;
    State m_initialization;
    State m_running;
    State m_shutdown;
};
