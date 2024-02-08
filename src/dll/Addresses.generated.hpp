#pragma once

/*
 * This file is generated. DO NOT modify it!
 *
 * Add new patterns in "patterns.py" file located in "project_root/scripts" and run "find_patterns.py".
 * The new file should be located in "idb_path/Addresses.hpp".
 */
#include <cstdint>

// Addresses for Cyberpunk 2077, version 2.11.
// clang-format off
namespace AddressesGen
{
constexpr uintptr_t ImageBase = 0x140000000;

#pragma region CBaseFunction
constexpr uintptr_t CBaseFunction_Handlers = 0x143332C50 - ImageBase; // 4C 8D 05 ? ? ? ? 48 8D 0D ? ? ? ? 4C 89 9B ? ? ? ?, expected: 2, index: 1, offset: 3
#pragma endregion

#pragma region CGameEngine
constexpr uintptr_t CGameEngine = 0x1433769B8 - ImageBase; // 48 89 05 ? ? ? ? 48 8B D8 48 8B 10 FF 92 ? ? ? ?, expected: 1, index: 0, offset: 3
#pragma endregion

#pragma region CRTTIRegistrator
constexpr uintptr_t CRTTIRegistrator_RTTIAsyncId = 0x143EF2A0C - ImageBase; // F0 0F C1 05 ? ? ? ? FF C0 48 8D 0D ? ? ? ? 89 05 ? ? ? ? E8 ? ? ? ?, expected: 11821, index: 0, offset: 4
#pragma endregion

#pragma region CStack
constexpr uintptr_t CStack_vtbl = 0x142A462B0 - ImageBase; // 48 8D 05 ? ? ? ? 48 89 45 ? 48 8D 45 ? 48 89 45 ? 66 0F 7F 45 ?, expected: 1, index: 0, offset: 3
#pragma endregion

#pragma region JobDispatcher
constexpr uintptr_t JobDispatcher = 0x1433844E0 - ImageBase; // 48 89 05 ? ? ? ? 48 83 C4 ? 5F C3, expected: 6, index: 4, offset: 3
#pragma endregion

#pragma region Memory
constexpr uintptr_t Memory_Vault = 0x143384640 - ImageBase; // C6 04 0A 01 48 8D 0D ? ? ? ? 8B 50 ? 48 8B C1, expected: 2, index: 0, offset: 7
#pragma endregion

#pragma region OpcodeHandlers
constexpr uintptr_t OpcodeHandlers = 0x1432F2C50 - ImageBase; // 4C 8D 05 ? ? ? ? 48 8D 0D ? ? ? ? 4C 89 9B ? ? ? ?, expected: 2, index: 0, offset: 3
#pragma endregion

#pragma region ResourceDepot
constexpr uintptr_t ResourceDepot = 0x1448345D8 - ImageBase; // 48 89 05 ? ? ? ? 49 8B 5B ? 49 8B 73, expected: 1, index: 0, offset: 3
#pragma endregion

#pragma region ResourceLoader
constexpr uintptr_t ResourceLoader = 0x143372C58 - ImageBase; // 48 89 05 ? ? ? ? 48 83 C4 ? 5F C3, expected: 6, index: 2, offset: 3
#pragma endregion
} // namespace AddressesGen
// clang-format on
