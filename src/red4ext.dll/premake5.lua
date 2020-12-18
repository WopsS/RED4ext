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
        red4ext.project.includes("RenHook"),
        red4ext.project.includes("spdlog")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        red4ext.project.links("RenHook"),
        red4ext.project.links("spdlog")
    })
