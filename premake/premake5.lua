require("premake", ">=5.0.0-alpha16")

red4ext = require("extensions/red4ext")

workspace("RED4ext")
    location("projects")
    startproject("RED4ext.Loader")

    architecture("x86_64")
    configurations({ "Debug", "Release" })
    characterset("Unicode")
    symbols("Full")
    systemversion("latest")
    vectorextensions("SSE3")

    defines(
    {
        "WINVER=0x0601",
        "_WIN32_WINNT=0x0601",
        "WIN32_LEAN_AND_MEAN",
        "_CRT_SECURE_NO_WARNINGS",
        "NOMINMAX"
    })

    filter({ "configurations:Release" })
        optimize("On")

    filter({ "language:C++" })
        cppdialect("C++20")

    filter({})

    group("Dependencies")
        include(red4ext.paths.modules("Detours"))
        include(red4ext.paths.modules("fmt"))
        include(red4ext.paths.modules("spdlog"))

    group("")
        include(red4ext.paths.src("red4ext.dll"))
        include(red4ext.paths.src("red4ext.loader"))
        include(red4ext.paths.src("red4ext.playground"))
        include(red4ext.paths.example())
