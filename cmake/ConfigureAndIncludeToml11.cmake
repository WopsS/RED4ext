add_subdirectory(deps/toml11)

mark_as_advanced(
  CMAKE_CXX_EXTENSIONS
  CMAKE_CXX_STANDARD_REQUIRED
  toml11_BUILD_TEST
  toml11_INSTALL
  toml11_TEST_WITH_ASAN
  toml11_TEST_WITH_UBSAN
)
