#pragma once

/*
 * This file is generated. DO NOT modify it!
 *
 * Add new patterns in "patterns.py" file located in "project_root/scripts" and run "find_patterns.py".
 * The new file should be located in "idb_path/Addresses.hpp".
 */
#include <cstdint>

// Addresses for Cyberpunk 2077, version 1.62.
namespace Addresses
{
constexpr uintptr_t ImageBase = 0x140000000;

#pragma region CGameApplication
constexpr uintptr_t CGameApplication_Run = 0x140A80460 - ImageBase; // 48 89 5C 24 08 57 48 83 EC 20 48 8B D9 33 FF 90, expected: 3, index: 0
#pragma endregion

#pragma region CInitializationState
constexpr uintptr_t CInitializationState_Run = 0x140A82030 - ImageBase; // 48 83 EC 28 48 8B 05 ? ? ? ? 4C 8B C2 8B 88 F8 00 00 00, expected: 1, index: 0
#pragma endregion

#pragma region CRunningState
constexpr uintptr_t CRunningState_Run = 0x140A82170 - ImageBase; // 40 53 48 83 EC 20 48 8B 0D ? ? ? ? 48 8B DA E8 ? ? ? ? 84 C0, expected: 1, index: 0
#pragma endregion

#pragma region CShutdownState
constexpr uintptr_t CShutdownState_Run = 0x140A82280 - ImageBase; // 48 89 6C 24 18 56 48 83 EC 30 48 8B 0D ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region Global
constexpr uintptr_t Global_Main = 0x1401A0330 - ImageBase; // 40 53 48 81 EC ? ? ? ? FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?, expected: 1, index: 0
#pragma endregion
} // namespace Addresses
