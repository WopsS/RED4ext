project("RED4ext.SDK")
    targetname("RED4ext.SDK")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C++")

    includedirs(
    {
        "."
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })
