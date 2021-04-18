local m = {}

local currentDir = os.getcwd();
function m.root()
    return path.getdirectory(path.getdirectory(path.getdirectory(currentDir)));
end

function m.build(path1, ...)
    return path.join(m.root(), "build", "%{cfg.buildcfg:lower()}", path1, ...)
end

function m.deps(path1, ...)
    return path.join(m.root(), "deps", path1, ...)
end

function m.example()
    return path.join(m.root(), "example")
end

function m.modules(module)
    return path.join(m.root(), "premake", "modules", module)
end

function m.src(path1, ...)
    return path.join(m.root(), "src", path1, ...)
end

return m
