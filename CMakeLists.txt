cmake_minimum_required(VERSION 3.23)

project(RED4ext LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(ConfigureVersionFromGit)
include(ConfigureDefaultOutputDirectories)
include(TargetOutputDirectory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

configure_version_from_git()
configure_default_output_directories()

add_compile_definitions(
  # Support Windows 7 and above.
  WINVER=0x0601
  _WIN32_WINNT=0x0601

  # Exclude unnecessary APIs.
  WIN32_LEAN_AND_MEAN

  # Use Unicode charset.
  UNICODE
  _UNICODE
)

add_compile_options(
  # Enable correct reporting of C++ version, see https://docs.microsoft.com/en-us/cpp/build/reference/zc-cplusplus.
  $<$<BOOL:MSVC>:/Zc:__cplusplus>

  # Mark all dependencies headers as external.
  $<$<BOOL:MSVC>:/external:I${PROJECT_SOURCE_DIR}/deps>

  # Set the default warning level for external includes.
  $<$<BOOL:MSVC>:/external:W0>

  # Allow warnings if some template code is used in our code base.
  $<$<BOOL:MSVC>:/external:templates->
)

include(ConfigureAndIncludeDetours)
include(ConfigureAndIncludeFmt)
include(ConfigureAndIncludeRED4extSdk)
include(ConfigureAndIncludeSimdjson)
include(ConfigureAndIncludeSpdlog)
include(ConfigureAndIncludeToml11)
include(ConfigureAndIncludeTslOrderedMap)
include(ConfigureAndIncludeWil)
include(ConfigureAndIncludeRedscript)

option(RED4EXT_EXTRA_WARNINGS "Enable extra warnings." ON)
if(RED4EXT_EXTRA_WARNINGS)
  if(MSVC)
    add_compile_options(/W4)
  else()
    add_compile_options(-Wall -Wextra)
  endif()
endif()

option(RED4EXT_TREAT_WARNINGS_AS_ERRORS "Treat compiler warnings as errors." OFF)
if(RED4EXT_TREAT_WARNINGS_AS_ERRORS)
  if(MSVC)
    add_compile_options(/WX)
  else()
    add_compile_options(-Werror)
  endif()
endif()

add_subdirectory(src)
