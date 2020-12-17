project("Zycore")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C")

    includedirs(
    {
        red4ext.paths.deps("zyantific"),
        red4ext.paths.deps("renhook", "deps", "zydis", "dependencies", "zycore", "include")
    })

    files(
    {
        red4ext.paths.deps("renhook", "deps", "zydis", "dependencies", "zycore", "src", "**.c"),
        red4ext.paths.deps("renhook", "deps", "zydis", "dependencies", "zycore", "include", "**.h")
    })
