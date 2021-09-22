project("RED4ext.Dll")
    targetname("RED4ext")
    targetdir(red4ext.paths.build("bin"))
    implibdir(red4ext.paths.build("libs"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")

    defines(
    {
        red4ext.project.defines("spdlog")
    })

    includedirs(
    {
        ".",
        red4ext.project.includes("Detours"),
        red4ext.project.includes("spdlog"),
        red4ext.paths.deps("red4ext.sdk", "include"),
        red4ext.paths.deps("toml++", "include")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        "version",
        red4ext.project.links("Detours"),
        red4ext.project.links("spdlog")
    })
