project("RED4ext.Example")
    targetdir(red4ext.paths.build("bin", "plugins"))

    kind("SharedLib")
    language("C++")
    dependson({ "RED4ext.Dll" })

    includedirs(
    {
        ".",
        red4ext.paths.deps("red4ext.sdk", "include")
    })

    files(
    {
        "**.cpp",
        "**.hpp"
    })

    links(
    {
        "Dbghelp"
    })
