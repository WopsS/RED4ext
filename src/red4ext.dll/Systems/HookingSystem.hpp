#pragma once

#include "PluginBase.hpp"
#include "Hook.hpp"

class HookingSystem
{
public:
    void Shutdown();

    bool Attach(std::shared_ptr<PluginBase> aPlugin, void* aTarget, void* aDetour, void** aOriginal);
    bool Detach(std::shared_ptr<PluginBase> aPlugin, void* aTarget);

private:
    struct Item
    {
        Item(void* aTarget, void* aDetour, void** aOriginal)
            : target(aTarget)
            , original(aOriginal)
            , hook(aTarget, aDetour)
        {
        }

        void* target;
        void** original;
        Hook<void*> hook;
    };
    
    using Map_t = std::unordered_multimap<std::shared_ptr<PluginBase>, Item>;
    using MapIter_t = Map_t::iterator;

    bool QueueForDetach(std::shared_ptr<PluginBase> aPlugin, Item& aItem);

    std::mutex m_mutex;
    std::unordered_multimap<std::shared_ptr<PluginBase>, Item> m_hooks;
};
