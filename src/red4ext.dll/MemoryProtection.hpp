#pragma once

class MemoryProtection
{
public:
    struct Exception : public std::exception
    {
        Exception();

        uint32_t GetLastError() const;

    private:
        uint32_t m_lastError;
    };

    MemoryProtection(void* aAddress, size_t aSize, uint32_t aProtection);
    ~MemoryProtection();

    MemoryProtection(MemoryProtection&) = delete;
    MemoryProtection(MemoryProtection&&) = delete;

    MemoryProtection& operator=(const MemoryProtection&) = delete;
    MemoryProtection& operator=(MemoryProtection&&) = delete;

private:
    void* m_address;
    size_t m_size;
    uint32_t m_oldProtection;
    bool m_shouldRestore;
};
