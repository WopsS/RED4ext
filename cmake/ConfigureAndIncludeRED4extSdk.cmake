add_subdirectory(deps/red4ext.sdk)
set_target_properties(RED4ext.SDK PROPERTIES FOLDER "Dependencies")

mark_as_advanced(
  RED4EXT_BUILD_EXAMPLES
  RED4EXT_HEADER_ONLY
)
