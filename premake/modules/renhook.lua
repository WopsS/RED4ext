project("RenHook")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C++")

    filter({ "configurations:Debug" })
        optimize("On")
        runtime("Debug")

    filter({})

    includedirs(
    {
        red4ext.paths.deps("renhook", "src"),
        red4ext.project.includes("Zydis")
    })

    files(
    {
        red4ext.paths.deps("renhook", "src", "**.cpp"),
        red4ext.paths.deps("renhook", "src", "**.hpp")
    })

    links(
    {
        red4ext.project.links("Zydis")
    })
