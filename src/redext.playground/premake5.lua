project("REDext.Playground")
    targetdir(redext.paths.build("bin", "plugins"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")

    defines(
    {
        redext.project.defines("spdlog")
    })

    includedirs(
    {
        ".",
        redext.project.includes("REDext.SDK"),
        redext.project.includes("RenHook"),
        redext.project.includes("spdlog")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        redext.project.links("REDext.SDK"),
        redext.project.links("RenHook"),
        redext.project.links("spdlog")
    })
