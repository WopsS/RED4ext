project("RED4ext.Loader")
    targetname("d3d11")
    targetdir(red4ext.paths.build("bin"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "RED4ext.Dll" })

    -- Remove these defines, else Resource Compiler will cry.
    removedefines({
        "WINVER=*",
        "_WIN32_WINNT=*"
    })

    defines(
    {
        "WINVER=0x0A00",
        "_WIN32_WINNT=0x0A00"
    })

    includedirs(
    {
        ".",
        red4ext.project.includes("fmt"),
        red4ext.paths.deps("wil", "include")
    })

    files(
    {
        "**.cpp",
        "**.hpp",
        "**.def",
        "**.rc"
    })

    links(
    {
        red4ext.project.links("fmt")
    })
