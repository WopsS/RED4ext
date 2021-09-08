#include "stdafx.hpp"
#include "TrampolinesManager.hpp"

void* TrampolinesManager::Alloc(std::shared_ptr<PluginBase> aPlugin)
{
    constexpr auto twoGbInBytes = std::numeric_limits<int32_t>::max();
    constexpr auto maxPointerAddress = std::numeric_limits<uintptr_t>::max();

    // Used to prevent upper bound overflow.
    constexpr auto maxUpperBoundMemory = maxPointerAddress - twoGbInBytes;

    //auto middle = (renhook::executable::get_code_base_address() + renhook::executable::get_code_end_address()) / 2;
    auto middle = 0;

    auto lowerBound = middle;
    auto upperBound = middle;

    if (lowerBound > twoGbInBytes)
    {
        lowerBound -= twoGbInBytes;
    }

    if (upperBound < maxUpperBoundMemory)
    {
        upperBound += twoGbInBytes;
    }

    std::scoped_lock<std::mutex> _(m_mutex);

    /*auto trampoline = m_allocator.alloc(lowerBound, upperBound);
    if (trampoline)
    {
        m_trampolines.emplace(aPlugin, trampoline);
        return trampoline;
    }*/

    return nullptr;
}

void TrampolinesManager::Free(std::shared_ptr<PluginBase> aPlugin, void* aMemory)
{
    std::scoped_lock<std::mutex> _(m_mutex);

    auto range = m_trampolines.equal_range(aPlugin);
    for (auto it = range.first; it != range.second; ++it)
    {
        const auto memory = it->second;
        if (memory == aMemory)
        {
            //m_allocator.free(aMemory);
            m_trampolines.erase(it);

            break;
        }
    }
}

void TrampolinesManager::FreeAll()
{
    std::scoped_lock<std::mutex> _(m_mutex);
    for (const auto [plugin, memory] : m_trampolines)
    {
        //m_allocator.free(memory);
    }

    m_trampolines.clear();
}

void TrampolinesManager::FreeAll(std::shared_ptr<PluginBase> aPlugin)
{
    std::scoped_lock<std::mutex> _(m_mutex);

    auto range = m_trampolines.equal_range(aPlugin);
    for (auto it = range.first; it != range.second; ++it)
    {
        const auto memory = it->second;
        //m_allocator.free(memory);
    }

    m_trampolines.erase(aPlugin);
}
