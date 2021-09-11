project("RED4ext.Loader")
    targetname("version")
    targetdir(red4ext.paths.build("bin"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "RED4ext.Dll" })

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
