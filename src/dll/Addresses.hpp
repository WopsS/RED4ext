#pragma once

#include <cstdint>
#include <filesystem>
#include <unordered_map>

#include "Paths.hpp"

class Addresses
{
public:
    static void Construct(const Paths& aPaths);
    static Addresses* Instance();

    ~Addresses() = default;

    std::uintptr_t Resolve(const std::uint64_t aHash) const;

private:
    Addresses(const Paths& aPaths);

    void LoadAddresses(const std::filesystem::path& aPath);

    std::unordered_map<std::uint64_t, std::uintptr_t> m_addresses;
};
