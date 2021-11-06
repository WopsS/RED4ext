#pragma once

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <memory>
#include <mutex>
#include <unordered_set>
#include <source_location>
#include <string>
#include <string_view>
#include <system_error>

#include <Windows.h>
#include <detours.h>
#include <tlhelp32.h>

#include <wil/resource.h>
#include <wil/stl.h>
#include <wil/win32_helpers.h>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/xchar.h>

#include <spdlog/spdlog.h>
#include <toml.hpp>
#include <tsl/ordered_map.h>

#include <RED4ext/RED4ext.hpp>
