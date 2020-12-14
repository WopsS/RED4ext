local m = {}

local currentDir = os.getcwd();
function m.root()
    return path.getdirectory(path.getdirectory(path.getdirectory(currentDir)));
end

function m.build(path1, ...)
    return path.join(m.root(), "build", "%{cfg.buildcfg:lower()}", path1, ...)
end

function m.src(project)
    return path.join(m.root(), "src", project)
end

return m
