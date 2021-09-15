#pragma once

class DetourThreadsUpdater
{
public:
    DetourThreadsUpdater();
    DetourThreadsUpdater(DetourThreadsUpdater&) = delete;
    DetourThreadsUpdater(DetourThreadsUpdater&&) = delete;

    ~DetourThreadsUpdater();

    DetourThreadsUpdater& operator=(const DetourThreadsUpdater&) = delete;
    DetourThreadsUpdater& operator=(DetourThreadsUpdater&&) = delete;

private:
    void Update();
    void Release();

    std::vector<HANDLE> m_handles;
};
