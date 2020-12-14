project("REDext.SDK")
    targetname("REDext.SDK")
    targetdir(redext.paths.build("libs"))

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
