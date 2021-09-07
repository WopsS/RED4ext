project("spdlog")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C++")

    defines(
    {
        "SPDLOG_COMPILED_LIB",
        "SPDLOG_FMT_EXTERNAL",
        "SPDLOG_NO_THREAD_ID",
        "SPDLOG_WCHAR_FILENAMES",
        "SPDLOG_WCHAR_TO_UTF8_SUPPORT",
        "SPDLOG_DISABLE_DEFAULT_LOGGER"
    })

    includedirs(
    {
        red4ext.paths.deps("spdlog", "include"),
        red4ext.project.includes("fmt")
    })

    files(
    {
        red4ext.paths.deps("spdlog", "src", "**.cpp"),
        red4ext.paths.deps("spdlog", "include", "**.h"),
    })

    links(
    {
        red4ext.project.links("fmt")
    })
