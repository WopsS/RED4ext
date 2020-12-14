require("premake", ">=5.0.0-alpha15")

-- Disable premake.downloadModule, see https://github.com/premake/premake-core/issues/1381.
premake.downloadModule = function(modname, versions)
    return false
end

redext = require("extensions/redext")

workspace("REDext")
    location("projects")
    startproject("REDext.Loader")

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
        include(redext.paths.modules("spdlog"))

    group("")
        include(redext.paths.src("redext.dll"))
        include(redext.paths.src("redext.loader"))
        include(redext.paths.src("redext.sdk"))
