#pragma once

/*
 * This file is generated. DO NOT modify it!
 *
 * Add new patterns in "patterns.py" file located in "project_root/scripts" and run "find_patterns.py".
 * The new file should be located in "idb_path/Addresses.hpp".
 */
#include <cstdint>

// Addresses for Cyberpunk 2077, version 1.31.
namespace Addresses
{
constexpr uintptr_t ImageBase = 0x140000000;

#pragma region CInitializationState
constexpr uintptr_t CInitializationState_Run = 0x140AD61A0 - ImageBase; // 48 83 EC 28 48 8B 05 ? ? ? ? 4C 8B C2 8B 88 F8 00 00 00, expected: 1, index: 0
#pragma endregion

#pragma region CShutdownState
constexpr uintptr_t CShutdownState_Run = 0x140AD6380 - ImageBase; // 48 89 6C 24 18 56 48 83 EC 30 48 8B 0D ? ? ? ?, expected: 1, index: 0
#pragma endregion

#pragma region Global
constexpr uintptr_t Global_Main = 0x1401BB560 - ImageBase; // 40 53 48 81 EC C0 01 00 00 FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?, expected: 1, index: 0
#pragma endregion
} // namespace RED4ext::Addresses
