project("RED4ext.Playground")
    targetdir(red4ext.paths.build("bin", "plugins"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "RED4ext.Dll" })

    defines(
    {
        red4ext.project.defines("spdlog")
    })

    libdirs(
    {
        red4ext.paths.build("libs")
    })

    includedirs(
    {
        ".",
        red4ext.project.includes("RenHook"),
        red4ext.project.includes("spdlog"),
        red4ext.paths.src("red4ext.sdk", "include")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        "Dbghelp",
        red4ext.project.links("RenHook"),
        red4ext.project.links("spdlog"),
        red4ext.project.links("RED4ext.Dll")
    })
