project("RED4ext.Loader")
    targetname("powrprof")
    targetdir(red4ext.paths.build("bin"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "RED4ext.Dll" })

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
        "**.def"
    })

    links(
    {
        red4ext.project.links("fmt")
    })
