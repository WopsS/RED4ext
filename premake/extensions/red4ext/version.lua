local m = {}
local paths = require("red4ext/paths")

function m.gen()
    local content = string.format("#pragma once\n\n", tag)

    local tags = string.explode(os.outputof("git tag --sort -version:creatordate"), "\n")
    if #tags > 0 then
        local latest = tags[1]

        if string.startswith(latest, "v") then
            latest = latest:sub(2)
        end

        local version = string.explode(latest:escapepattern(), string.escapepattern("."))
        local major = version[1]
        local minor = version[2]
        local patch = version[3]

        local version_str = string.format("v%s.%s.%s", major, minor, patch)

        local branch = os.outputof("git rev-parse --abbrev-ref HEAD")
        local commit = os.outputof("git rev-parse --short HEAD")
        local metadata = string.format("%s.%s", branch, commit)

        local commits_diff = os.outputof(string.format("git rev-list --count v%s..HEAD", latest))
        commits_diff = tonumber(commits_diff)
        if commits_diff > 0 then
            metadata = string.format("%s.%d.%s", branch, commits_diff, commit)
        end

        content = content .. string.format([[
#define RED4EXT_VERSION_MAJOR %d
#define RED4EXT_VERSION_MINOR %d
#define RED4EXT_VERSION_PATCH %d

#define RED4EXT_VERSION_METADATA "%s"
]], major, minor, patch, metadata)

        if commits_diff > 0 then
            content = content .. string.format([[
#define RED4EXT_VERSION_STR "%s+" RED4EXT_VERSION_METADATA
]], version_str)
        else
            content = content .. string.format([[
#define RED4EXT_VERSION_STR "%s"
]], version_str)
        end
    end

    local file = red4ext.paths.src("red4ext.dll", "Version.hpp")

    local current = io.readfile(file)
    if current == content then
        return
    end

    io.writefile(file, content)
end

return m
