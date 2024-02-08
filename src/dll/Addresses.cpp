#include "Addresses.hpp"

#include <ios>
#include <string>
#include <string_view>

#include <RED4ext/Relocation.hpp>
#include <spdlog/spdlog.h>

#include "Utils.hpp"

namespace
{
std::unique_ptr<Addresses> g_addresses;
}

Addresses::Addresses(const Paths& aPaths)
{
    constexpr auto filename = L"cyberpunk2077_addresses.json";
    auto filePath = aPaths.GetX64Dir() / filename;

    LoadAddresses(filePath);
}

void Addresses::Construct(const Paths& aPaths)
{
    g_addresses.reset(new Addresses(aPaths));
}

Addresses* Addresses::Instance()
{
    return g_addresses.get();
}

std::uintptr_t Addresses::Resolve(const RED4ext::UniversalRelocSegment aSegment, const std::uint64_t aHash) const
{
    auto it = m_addresses.find(aHash);
    if (it == m_addresses.end())
    {
        return 0;
    }

    auto address = it->second;
    switch (aSegment)
    {
    case RED4ext::UniversalRelocSegment::Text:
    {
        return address + m_codeOffset;
    }
    default:
    {
        return address;
    }
    }
}

void Addresses::LoadAddresses(const std::filesystem::path& aPath)
{
    if (!std::filesystem::exists(aPath))
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"The addresses JSON does not exists\n\nPath: {}", aPath);
        return;
    }

    spdlog::info(L"Loading game's addresses from '{}'...", aPath);

    simdjson::ondemand::parser parser;
    simdjson::padded_string json = simdjson::padded_string::load(aPath.string());
    simdjson::ondemand::document document = parser.iterate(json);

    simdjson::ondemand::array root;
    auto error = document.get_array().get(root);
    if (error)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"Could not get the root array for the addresses: {}",
                                            Utils::Widen(simdjson::error_message(error)));
        return;
    }

    if (root.count_elements() != 2)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"The root array for the addresses does not have 2 elements");
        return;
    }

    simdjson::ondemand::array knownAddresses = root.at(0);

    std::string_view codeOffsetStr;
    error = knownAddresses.at(0)["Code constant offset"].get_string().get(codeOffsetStr);
    if (error)
    {
        SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"Could not get the code constant offset for an address: {}",
                                            Utils::Widen(simdjson::error_message(error)));
        return;
    }

    m_codeOffset = std::stoull(codeOffsetStr.data(), nullptr, 16);
    auto base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(nullptr));

    root.reset();
    for (auto array : root)
    {
        for (auto entry : array)
        {
            auto hashField = entry.find_field("hash");
            auto offsetField = entry.find_field("offset");

            if (!hashField.error() && !offsetField.error())
            {
                std::uint64_t hash;
                error = hashField.get_uint64_in_string().get(hash);
                if (error)
                {
                    SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"Could not get the hash for an address: {}",
                                                        Utils::Widen(simdjson::error_message(error)));
                    return;
                }

                std::string_view offsetStr;
                error = offsetField.get_string().get(offsetStr);
                if (error)
                {
                    SHOW_MESSAGE_BOX_AND_EXIT_FILE_LINE(L"Could not get the offset for an address: {}",
                                                        Utils::Widen(simdjson::error_message(error)));
                    return;
                }

                std::stringstream stream;
                stream << offsetStr;

                std::uintptr_t offset;
                stream >> std::hex >> offset;

                auto address = offset + base;
                m_addresses.emplace(hash, address);
            }
        }
    }

    spdlog::info("{} game addresses loaded", m_addresses.size());
}

RED4EXT_C_EXPORT std::uintptr_t RED4EXT_CALL RED4ext_ResolveAddress(const RED4ext::UniversalRelocSegment aSegment,
                                                                    const std::uint64_t aHash)
{
    return Addresses::Instance()->Resolve(aSegment, aHash);
}
