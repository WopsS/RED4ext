#pragma once

/*
 * This file is generated. DO NOT modify it!
 *
 * Add new patterns in "patterns.py" file located in "project_root/scripts" and run "find_patterns.py".
 * The new file should be located in "idb_path/Addresses.hpp".
 */
#include <cstdint>

// Addresses for Cyberpunk 2077, version 2.01.
namespace Addresses
{
constexpr uintptr_t ImageBase = 0x140000000;

#pragma region CBaseEngine
constexpr uintptr_t CBaseEngine_InitScripts = 0x14070F590 - ImageBase; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 41 0F B7 F1, expected: 1, index: 0
constexpr uintptr_t CBaseEngine_LoadScripts = 0x140710168 - ImageBase; // 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 49 8D 99 ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region CGameApplication
constexpr uintptr_t CGameApplication_AddState = 0x14080E184 - ImageBase; // 48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B 02 48 8D B9 ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region CInitializationState
constexpr uintptr_t CInitializationState_Run = 0x14080DE30 - ImageBase; // 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 33 DB 4C 8B C2 8B 88 ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region CRunningState
constexpr uintptr_t CRunningState_Run = 0x14080DDCC - ImageBase; // 40 53 48 83 EC ? 83 64 24 ? ? 48 8D 05 ? ? ? ? 48 8B 0D ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region CShutdownState
constexpr uintptr_t CShutdownState_Run = 0x140A4DFD8 - ImageBase; // 40 53 48 83 EC ? 48 8B DA E8 ? ? ? ? 48 8B CB 89 83 ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region Global
constexpr uintptr_t Global_Main = 0x14080E01C - ImageBase; // 40 55 53 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? FF 15 ? ? ? ?, expected: 1, index: 0
constexpr uintptr_t Global_ExecuteProcess = 0x14070FD24 - ImageBase; // 48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 41 81 79 ? ? ? ? ?, expected: 1, index: 0
#pragma endregion
} // namespace Addresses
