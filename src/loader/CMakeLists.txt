add_library(RED4ext.Loader SHARED)

set_target_properties(RED4ext.Loader PROPERTIES OUTPUT_NAME winmm)

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE DEF_FILES *.def)
file(GLOB_RECURSE RC_FILES *.rc)

source_group(_CMake REGULAR_EXPRESSION cmake_pch.*)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES} ${DEF_FILES} ${RC_FILES})

target_include_directories(RED4ext.Loader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(RED4ext.Loader PRIVATE ${HEADER_FILES} ${SOURCE_FILES} ${DEF_FILES} ${RC_FILES})

target_precompile_headers(RED4ext.Loader PRIVATE stdafx.hpp)
target_link_libraries(RED4ext.Loader PRIVATE fmt WIL)
