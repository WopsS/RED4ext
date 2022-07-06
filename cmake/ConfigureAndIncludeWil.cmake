option(WIL_BUILD_TESTS "" OFF)
option(WIL_BUILD_PACKAGING "" OFF)

add_subdirectory(deps/wil)

mark_as_advanced(
  FAST_BUILD
  WIL_BUILD_PACKAGING
  WIL_BUILD_TESTS
)
