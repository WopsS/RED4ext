project("REDext.Loader")
    targetname("REDext")
    targetdir(redext.paths.build("bin"))
    symbolspath(redext.paths.build("bin", "REDext.Loader.pdb"))

    kind("ConsoleApp")
    language("C++")
    pchheader("stdafx.hpp")
    pchsource("stdafx.cpp")
    dependson({ "REDext.Dll" })

    includedirs(
    {
        "."
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })
