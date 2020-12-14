project("REDext.Dll")
    targetname("REDext")
    targetdir(redext.paths.build("bin"))

    kind("SharedLib")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")

    includedirs(
    {
        "."
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })
