local m = {}
local paths = require("red4ext/paths")

function m.gen()
    local tag = os.outputof("git describe --tags")

    local content = string.format([[
#pragma once

#define RED4EXT_GIT_TAG "%s"
]], tag)

    local file = red4ext.paths.src("red4ext.dll", "Version.hpp")

    local current = io.readfile(file)
    if current == content then
        return
    end

    io.writefile(file, content)
end

return m
