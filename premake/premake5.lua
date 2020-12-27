require("premake", ">=5.0.0-alpha15")

-- Disable premake.downloadModule, see https://github.com/premake/premake-core/issues/1381.
premake.downloadModule = function(modname, versions)
    return false
end

red4ext = require("extensions/red4ext")

workspace("RED4ext")
    location("projects")
    startproject("RED4ext.Loader")

    architecture("x86_64")
    configurations({ "Debug", "Release" })
    characterset("Unicode")
    symbols("Full")

    filter({ "action:vs*", "language:c or language:c++" })
        systemversion("latest")

        defines(
        {
            "WINVER=0x0601",
            "_WIN32_WINNT=0x0601",
            "WIN32_LEAN_AND_MEAN",
            "_CRT_SECURE_NO_WARNINGS"
        })

    filter({ "configurations:Release" })
        optimize("On")

    filter({ "language:C++" })
        cppdialect("C++17")

    filter({})

    group("Dependencies")
        include(red4ext.paths.modules("spdlog"))

        include(red4ext.paths.modules("zycore"))
        include(red4ext.paths.modules("zydis"))
        include(red4ext.paths.modules("renhook"))

    group("")
        include(red4ext.paths.src("red4ext.dll"))
        include(red4ext.paths.src("red4ext.loader"))
        include(red4ext.paths.src("red4ext.playground"))
