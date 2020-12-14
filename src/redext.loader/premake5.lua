project("REDext.Loader")
    targetname("REDext")
    targetdir(redext.paths.build("bin"))
    symbolspath(redext.paths.build("bin", "REDext.Loader.pdb"))

    kind("ConsoleApp")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "REDext.Dll" })

    defines(
    {
        redext.project.defines("spdlog")
    })

    includedirs(
    {
        ".",
        redext.project.includes("spdlog")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        redext.project.links("spdlog")
    })
