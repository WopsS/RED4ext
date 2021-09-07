project("fmt")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C++")

    includedirs(
    {
        red4ext.paths.deps("fmt", "include")
    })

    files(
    {
        red4ext.paths.deps("fmt", "src", "format.cc"),
        red4ext.paths.deps("fmt", "src", "os.cc"),
        red4ext.paths.deps("fmt", "include", "**.h"),
    })
