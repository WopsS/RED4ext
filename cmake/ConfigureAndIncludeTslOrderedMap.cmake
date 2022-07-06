# Creating a library interface project.
# Including the original ordered_map project will also bring source files to the project that links it and it becomes ugly.

add_library(ordered_map INTERFACE)
add_library(tsl::ordered_map ALIAS ordered_map)

target_include_directories(ordered_map INTERFACE "${PROJECT_SOURCE_DIR}/deps/ordered-map/include")
target_compile_definitions(ordered_map INTERFACE NOMINMAX)
