#include "stdafx.hpp"
#include "PluginBase.hpp"

PluginBase::PluginBase(RED4ext::PluginHandle aHandle)
    : m_handle(aHandle)
    , m_interface(nullptr)
{
}

void PluginBase::SetInterface(void* aInterface)
{
    m_interface = aInterface;
}

void* PluginBase::GetInterface() const
{
    return m_interface;
}

void PluginBase::AddTrampoline(void* aMemory)
{
    m_trampolines.emplace(aMemory);
}

void PluginBase::RemoveTrampoline(void* aMemory)
{
    m_trampolines.erase(aMemory);
}

const std::unordered_set<void*>& PluginBase::GetTrampolines() const
{
    return m_trampolines;
}

RED4ext::PluginHandle PluginBase::GetHandle() const
{
    return m_handle;
}
