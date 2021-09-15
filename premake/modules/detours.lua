project("Detours")
    targetdir(red4ext.paths.build("libs"))

    kind("StaticLib")
    language("C++")

    includedirs(
    {
        red4ext.paths.deps("detours", "src")
    })

    files(
    {
        red4ext.paths.deps("detours", "src", "**.cpp"),
        red4ext.paths.deps("detours", "src", "**.h"),
    })

    removefiles(
    {
        red4ext.paths.deps("detours", "src", "uimports.cpp")
    })
