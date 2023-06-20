#pragma once

/*
 * This file is generated. DO NOT modify it!
 *
 * Add new patterns in "patterns.py" file located in "project_root/scripts" and run "find_patterns.py".
 * The new file should be located in "idb_path/Addresses.hpp".
 */
#include <cstdint>

// Addresses for Cyberpunk 2077, version 1.63.
namespace Addresses
{
constexpr uintptr_t ImageBase = 0x140000000;

#pragma region CBaseEngine
constexpr uintptr_t CBaseEngine_InitScripts = 0x140A850B0 - ImageBase; // 48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 0F B7 D8 0F B6 FA 48 8B F1 E8, expected: 1, index: 0
constexpr uintptr_t CBaseEngine_LoadScripts = 0x140A85550 - ImageBase; // 48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 56 48 83 EC 20 49 8B F9 41 C6 81, expected: 1, index: 0
#pragma endregion

#pragma region CGameApplication
constexpr uintptr_t CGameApplication_Run = 0x140A81B30 - ImageBase; // 48 89 5C 24 08 57 48 83 EC 20 48 8B D9 33 FF 90, expected: 3, index: 0
#pragma endregion

#pragma region CInitializationState
constexpr uintptr_t CInitializationState_Run = 0x140A83790 - ImageBase; // 48 83 EC 28 48 8B 05 ? ? ? ? 4C 8B C2 8B 88 F8 00 00 00, expected: 1, index: 0
#pragma endregion

#pragma region CRunningState
constexpr uintptr_t CRunningState_Run = 0x140A838D0 - ImageBase; // 40 53 48 83 EC 20 48 8B 0D ? ? ? ? 48 8B DA E8 ? ? ? ? 84 C0, expected: 1, index: 0
#pragma endregion

#pragma region CShutdownState
constexpr uintptr_t CShutdownState_Run = 0x140A839E0 - ImageBase; // 48 89 6C 24 18 56 48 83 EC 30 48 8B 0D ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region Global
constexpr uintptr_t Global_Main = 0x1401A0550 - ImageBase; // 40 53 48 81 EC ? ? ? ? FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?, expected: 1, index: 0
constexpr uintptr_t Global_ExecuteProcess = 0x142C2B800 - ImageBase; // 48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B FA 48 8B F1 48 8D 54 24 30 49 8B C9 49 8B D8, expected: 1, index: 0
#pragma endregion
} // namespace Addresses
