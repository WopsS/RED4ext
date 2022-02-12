local m = {}

function m.defines(name)
    local workspace = premake.global.getWorkspace("RED4ext")
    local project = premake.workspace.findproject(workspace, name)

    if (project == null) then
        premake.error("Project '" .. name .. "' not found\n" .. debug.traceback())
    end

    return project.defines
end

function m.remove_defines(name, define)
    local workspace = premake.global.getWorkspace("RED4ext")
    local project = premake.workspace.findproject(workspace, name)

    if (project == null) then
        premake.error("Project '" .. name .. "' not found\n" .. debug.traceback())
    end

    local index = nil
    for i, d in ipairs(project.defines) do
        print(d)
        if d:startswith(define) then
            index = i
        end
    end
    print("")

    table.remove(project.defines, 2)
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

    if project.implibname then
        table.insert(links, project.implibname)
    elseif project.targetname then
        table.insert(links, project.targetname)
    else
        table.insert(links, project.name)
    end

    return links
end

return m
