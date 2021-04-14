#pragma once

#include "PluginBase.hpp"
#include "REDhook.hpp"

class HookingManager
{
public:
    HookingManager() = default;
    ~HookingManager() = default;

    void Create(std::shared_ptr<PluginBase> aPlugin, void* aTarget, void* aDetour, void** aOriginal);
    void Remove(std::shared_ptr<PluginBase> aPlugin, void* aTarget);

    void RemoveAll();
    void RemoveAll(std::shared_ptr<PluginBase> aPlugin);

    bool Attach(std::shared_ptr<PluginBase> aPlugin, void* aTarget);
    bool Detach(std::shared_ptr<PluginBase> aPlugin, void* aTarget);

    void AttachAll();
    void DetachAll();

    void DetachAll(std::shared_ptr<PluginBase> aPlugin);

private:
    struct HookItem
    {
        std::shared_ptr<PluginBase> plugin;
        void* target;
        void** original;

        std::unique_ptr<REDhook<>> hook;
    };

    bool Attach(const HookItem& aItem) const;
    bool Detach(const HookItem& aItem) const;

    std::recursive_mutex m_mutex;
    std::unordered_multimap<std::shared_ptr<PluginBase>, HookItem> m_hooks;
};
