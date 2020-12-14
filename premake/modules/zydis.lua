project("Zydis")
    targetdir(redext.paths.build("libs"))

    kind("StaticLib")
    language("C")

    includedirs(
    {
        redext.paths.deps("renhook", "deps", "zydis", "include"),
        redext.paths.deps("renhook", "deps", "zydis", "src"),
        redext.project.includes("Zycore")
    })

    files(
    {
        redext.paths.deps("renhook", "deps", "zydis", "src", "**.c"),
        redext.paths.deps("renhook", "deps", "zydis", "include", "**.h")
    })

    links(
    {
        "Zycore"
    })
