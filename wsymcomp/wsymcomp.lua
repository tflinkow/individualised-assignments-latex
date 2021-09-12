local wsymcomp = wsymcomp or {}

local actual = require "symcomp"

function basic(t)
    return t[1]
end

function latex(t)
    return t[2]
end

function requirestring(x)
    if type(x) == "string" then
        return x
    elseif type(x) == "table" then
        if #x == 2 then
            return basic(x)
        else
            error("TODO")
        end
    elseif type(x) == "number" then
        return tostring(x) -- TODO??
    else
        error("type '" .. type(x) .. "' is not supported")
    end
end

function requirenumber(x)
    if type(x) == "string" then
        return tonumber(x)
    elseif type(x) == "table" then
        if #x == 2 then
            return tonumber(basic(x))
        else
            error("TODO")
        end
    elseif type(x) == "number" then
        return x
    else
        error("type '" .. type(x) .. "' is not supported")
    end
end

function wsymcomp.expr(e)
    return actual.expr(e) -- no typecheck here, as actual will do that
end

-- returns f(x0) where f is a function of x
function wsymcomp.evalAt(f, x, x0)
    assert(type(x) == "string")

    -- actual.evalAt(string, string, number)
    return actual.evalAt(requirestring(f), x, requirenumber(x0))
end

-- returns the derivative of f with respect to x
function wsymcomp.diff(f, x)
    assert(type(x) == "string")
    
    -- actual.diff(string, string)
    return actual.diff(requirestring(f), requirestring(x))
end

-- subtracts b from a
function wsymcomp.sub(a, b)

    -- actual.sub(string, string)
    return actual.sub(requirestring(a), requirestring(b))
end

-- solves f(x) == 0
function wsymcomp.solve(f, x)
    assert(type(x) == "string")

    -- actual.solve(string, string)
    return actual.solve(requirestring(f), requirestring(x))
end

-- integrates f with respect to x from l to u
function wsymcomp.integrate(f, l, u, x)
    assert(type(x) == "string")

    -- actual.integrate(string, number, number, string)
    return actual.integrate(requirestring(f), requirenumber(l), requirenumber(u), requirestring(x))
end

return wsymcomp