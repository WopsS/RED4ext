local m = {}

function m.defines(name)
    local workspace = premake.global.getWorkspace("RED4ext")
    local project = premake.workspace.findproject(workspace, name)

    if (project == null) then
        premake.error("Project '" .. name .. "' not found\n" .. debug.traceback())
    end

    return project.defines
end

function m.includes(name)
    local workspace = premake.global.getWorkspace("RED4ext")
    local project = premake.workspace.findproject(workspace, name)

    if (project == null) then
        premake.error("Project '" .. name .. "' not found\n" .. debug.traceback())
    end

    return project.includedirs
end

function m.links(name)
    local workspace = premake.global.getWorkspace("RED4ext")
    local project = premake.workspace.findproject(workspace, name)

    if (project == null) then
        premake.error("Project '" .. name .. "' not found\n" .. debug.traceback())
    end

    local links = table.deepcopy(project.links)
    table.insert(links, name)

    return links
end

return m
