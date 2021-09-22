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

function requirestringdisplay(x)
    if type(x) == "string" then
        return x
    elseif type(x) == "table" then
        if #x == 2 then
            return latex(x)
        else
            error("TODO")
        end
    elseif type(x) == "number" then
        return tostring(x) -- TODO??
    else
        error("type '" .. type(x) .. "' is not supported")
    end
end

function fractiontonumber(x)
    -- turn '-1/2' into (-1) divided by (2) etc.
    idx = x:find("/")
    return tonumber(x:sub(1, idx - 1)) / tonumber(x:sub(idx + 1, #x))
end

function requirenumber(x)
    if type(x) == "string" then
        if x:find("/") then
            return fractiontonumber(x)
        else
            return tonumber(x)
        end
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

-- subtracts b from a (hence a - b)
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

function wsymcomp.getstringlatex(x)
    if type(x) == "table" then
        if #x == 2 then
            return latex(x)
        else
            return x
        end
    else
        return x
    end
end

function wsymcomp.getstringpgf(x)
    if type(x) == "table" then
        if #x == 2 then
            return basic(x):gsub("%*%*", "^")
        else
            return x
        end
    else
        return x
    end
end

function wsymcomp.findintersections(f, g, x)
    assert(type(x) == "string")

    h = wsymcomp.sub(f, g)
    intersections = wsymcomp.solve(h, x)

    return intersections
end

function wsymcomp.printintersections(f, g, x)
    assert(type(x) == "string")

    h = wsymcomp.sub(f, g)
    intersections = wsymcomp.solve(h, x)

    pretty = ""

    if #intersections == 0 then
        pretty = pretty .. "The functions do not intersect"
    else
        pretty = pretty .. "The functions intersect at "
    end

    for k, v in pairs(intersections) do
        -- f or g does not matter, f(x0)=g(x0) where x0 is intersection
        y = wsymcomp.evalAt(f, x, basic(v))

        if k == 1 then
        
        elseif k == #intersections then
            pretty = pretty .. " and at "
        else
            pretty = pretty .. ", "
        end

        pretty = pretty .. "$P_" .. k .. "(" .. latex(v) .. "," .. latex(y) .. ")^T$"
    end

    return pretty .. "."
end

function wsymcomp.printzeros(f, fname, x, startidx) -- startidx opt
    assert(type(x) == "string")

    startidx = startidx or 0

    zeros = wsymcomp.solve(f, x)

    pretty = "The function $" .. fname .. "$"

    if #zeros == 0 then
        pretty = pretty .. " does not have zeros"
    elseif #zeros == 1 then
        pretty = pretty .. " has a zero at "
    else
        pretty = pretty .. " has zeros at "
    end

    for k, v in pairs(zeros) do
        if k == 1 then
        
        elseif k == #zeros then
            pretty = pretty .. " and at "
        else
            pretty = pretty .. ", "
        end

        pretty = pretty .. "$" .. x .. "_" .. k + startidx .. "=" .. latex(v) .. "$"
    end

    return pretty .. "."
end

function wsymcomp.printminmax(f, fname, x)
    assert(type(x) == "string")

    diff1 = wsymcomp.diff(f, x)
    diff2 = wsymcomp.diff(diff1, x)
    zeros = wsymcomp.solve(diff1, x)

    fzeros = wsymcomp.solve(f, x) -- this is needed for correct indices

    pretty = "The function $" .. fname .. "$"

    if #zeros == 0 then
        pretty = pretty .. " does not have extremal points"
    else
        pretty = pretty .. " has"
    end

    for k, v in pairs(zeros) do
        y = wsymcomp.evalAt(diff2, x, basic(v))

        if k == 1 then
        
        elseif k == #zeros then
            pretty = pretty .. " and"
        else
            pretty = pretty .. ","
        end

        if tonumber(basic(y)) > 0 then
            pretty = pretty .. " a minimum"
        else -- todo: if == 0 then check inflection
            pretty = pretty .. " a maximum"
        end

        pretty = pretty .. " at $(" .. latex(v) .. "," .. latex(y) ..")$ because $" .. fname .. "''(" .. x .. "_" .. k + #fzeros .. ")"

        if tonumber(basic(y)) > 0 then
            pretty = pretty .. " > 0$"
        else -- todo: if == 0 then check inflection
            pretty = pretty .. " < 0$"
        end
    end

    return pretty .. "."
end

function wsymcomp.printintegral(f, u, l, x)
    assert(type(x) == "string")

    return "\\int_{" .. requirestringdisplay(u) .. "}^{" .. requirestringdisplay(l) .. "}{" .. requirestringdisplay(f) .. "}\\,\\mathrm{d}" .. x    
end

return wsymcomp