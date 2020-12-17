project("Zydis")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C")

    includedirs(
    {
        red4ext.paths.deps("renhook", "deps", "zydis", "include"),
        red4ext.paths.deps("renhook", "deps", "zydis", "src"),
        red4ext.project.includes("Zycore")
    })

    files(
    {
        red4ext.paths.deps("renhook", "deps", "zydis", "src", "**.c"),
        red4ext.paths.deps("renhook", "deps", "zydis", "include", "**.h")
    })

    links(
    {
        "Zycore"
    })
