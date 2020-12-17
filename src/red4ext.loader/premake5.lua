project("RED4ext.Loader")
    targetname("RED4ext")
    targetdir(red4ext.paths.build("bin"))
    symbolspath(red4ext.paths.build("bin", "RED4ext.Loader.pdb"))

    kind("ConsoleApp")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "RED4ext.Dll" })

    defines(
    {
        red4ext.project.defines("spdlog")
    })

    includedirs(
    {
        ".",
        red4ext.project.includes("spdlog")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        red4ext.project.links("spdlog")
    })
