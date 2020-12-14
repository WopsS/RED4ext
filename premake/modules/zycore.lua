project("Zycore")
    targetdir(redext.paths.build("libs"))

    kind("StaticLib")
    language("C")

    includedirs(
    {
        redext.paths.deps("zyantific"),
        redext.paths.deps("renhook", "deps", "zydis", "dependencies", "zycore", "include")
    })

    files(
    {
        redext.paths.deps("renhook", "deps", "zydis", "dependencies", "zycore", "src", "**.c"),
        redext.paths.deps("renhook", "deps", "zydis", "dependencies", "zycore", "include", "**.h")
    })
