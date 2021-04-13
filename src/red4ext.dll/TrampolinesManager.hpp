#pragma once

#include "PluginBase.hpp"

class TrampolinesManager
{
public:
    TrampolinesManager() = default;
    ~TrampolinesManager() = default;

    void* Alloc(std::shared_ptr<PluginBase> aPlugin);
    void Free(std::shared_ptr<PluginBase> aPlugin, void* aMemory);

    void FreeAll();
    void FreeAll(std::shared_ptr<PluginBase> aPlugin);

private:
    std::mutex m_mutex;

    renhook::memory::memory_allocator m_allocator;
    std::unordered_multimap<std::shared_ptr<PluginBase>, void*> m_trampolines;
};
