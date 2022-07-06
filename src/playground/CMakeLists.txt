add_library(RED4ext.Playground SHARED)

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)

source_group(_CMake REGULAR_EXPRESSION cmake_pch.*)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(RED4ext.Playground PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(RED4ext.Playground PRIVATE ${HEADER_FILES} ${SOURCE_FILES})

target_precompile_headers(RED4ext.Playground PRIVATE stdafx.hpp)
target_link_libraries(RED4ext.Playground PRIVATE RED4ext::SDK)

target_output_directory(RED4ext.Playground plugins)
