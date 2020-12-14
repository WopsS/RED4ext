project("RenHook")
    targetdir(redext.paths.build("libs"))

    kind("StaticLib")
    language("C++")

    filter({ "configurations:Debug" })
        optimize("On")
        runtime("Debug")

    filter({})

    includedirs(
    {
        redext.paths.deps("renhook", "src"),
        redext.project.includes("Zydis")
    })

    files(
    {
        redext.paths.deps("renhook", "src", "**.cpp"),
        redext.paths.deps("renhook", "src", "**.hpp")
    })

    links(
    {
        redext.project.links("Zydis")
    })
