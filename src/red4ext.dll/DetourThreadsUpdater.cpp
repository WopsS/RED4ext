#include "stdafx.hpp"
#include "DetourThreadsUpdater.hpp"

DetourThreadsUpdater::DetourThreadsUpdater()
{
    Update();
}

DetourThreadsUpdater::~DetourThreadsUpdater()
{
    Release();
}

void DetourThreadsUpdater::Update()
{
    auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        return;
    }

    THREADENTRY32 entry;
    entry.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(snapshot, &entry))
    {
        return;
    }

    auto processId = GetCurrentProcessId();
    auto threadId = GetCurrentThreadId();

    do
    {
        if (entry.th32OwnerProcessID == processId && entry.th32ThreadID != threadId)
        {
            auto handle = OpenThread(THREAD_GET_CONTEXT | THREAD_SUSPEND_RESUME, false, entry.th32ThreadID);
            if (!handle)
            {
                continue;
            }

            DetourUpdateThread(handle);
            m_handles.emplace_back(handle);
        }
    } while (Thread32Next(snapshot, &entry));
}

void DetourThreadsUpdater::Release()
{
    for (auto handle : m_handles)
    {
        CloseHandle(handle);
    }

    m_handles.clear();
}
