#pragma once

#include <cstdint>
#include <filesystem>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>

#include <Windows.h>
#include <ShlObj_core.h>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
