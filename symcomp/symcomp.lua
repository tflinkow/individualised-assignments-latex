local symcomp = symcomp or {}

local util = require "util"
local wsymengine = require "wsymengine"
local wsymmath = require "wsymmath"

function symcomp.expr(e)
    return wsymengine.expr(e) -- no typecheck here, as actual will do that
end

-- returns f(x0) where f is a function of x
function symcomp.evalAt(f, x, x0)
    return wsymengine.evalAt(util.BasicStringFromAny(f), util.BasicStringFromAny(x), util.NumberFromAny(x0))
end

-- returns the derivative of f with respect to x
function symcomp.diff(f, x)
    return wsymengine.diff(util.BasicStringFromAny(f), util.BasicStringFromAny(x))
end

-- TODO: remove after perf test
function symcomp.diff2(f, x)
    return wsymmath.diff(util.BasicStringFromAny(f), util.BasicStringFromAny(x))
end

-- subtracts b from a (hence a - b)
function symcomp.sub(a, b)
    return wsymengine.sub(util.BasicStringFromAny(a), util.BasicStringFromAny(b))
end

-- solves f(x) == 0
function symcomp.solve(f, x)
    return wsymengine.solve(util.BasicStringFromAny(f), util.BasicStringFromAny(x))
end

-- integrates f with respect to x from l to u, l and u optional
function symcomp.integrate(f, x, l, u)
    return wsymmath.integrate(util.BasicStringFromAny(f), util.BasicStringFromAny(x), util.BasicStringFromAny(l), util.BasicStringFromAny(u))
end

-- TODO: call the appropriate util funcs
function symcomp.getstringlatex(x)
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

-- TODO: call the appropriate util funcs
function symcomp.getstringpgf(x)
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

function symcomp.findintersections(f, g, x)
    h = symcomp.sub(f, g)
    intersections = symcomp.solve(h, x)

    return intersections
end

-- TODO: move to snippets
function symcomp.printintersections(f, g, x)
    h = symcomp.sub(f, g)
    intersections = symcomp.solve(h, x)

    pretty = ""

    if #intersections == 0 then
        pretty = pretty .. "The functions do not intersect"
    else
        pretty = pretty .. "The functions intersect at "
    end

    for k, v in pairs(intersections) do
        -- f or g does not matter, f(x0)=g(x0) where x0 is intersection
        y = symcomp.evalAt(f, x, basic(v))

        if k == 1 then
        
        elseif k == #intersections then
            pretty = pretty .. " and at "
        else
            pretty = pretty .. ", "
        end

        pretty = pretty .. "$P_" .. k .. "(" .. util.ExprRep.LaTeX(v) .. "," .. util.ExprRep.LaTeX(y) .. ")^T$"
    end

    return pretty .. "."
end

-- TODO: move to snippets
function symcomp.printzeros(f, fname, x, startidx) -- startidx opt
    startidx = startidx or 0

    zeros = symcomp.solve(f, x)

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

        pretty = pretty .. "$" .. util.LaTeXStringFromAny(x) .. "_" .. k + startidx .. "=" .. util.ExprRep.LaTeX(v) .. "$"
    end

    return pretty .. "."
end

-- TODO: move to snippets
function symcomp.printminmax(f, fname, x)
    diff1 = symcomp.diff(f, x)
    diff2 = symcomp.diff(diff1, x)
    zeros = symcomp.solve(diff1, x)

    fzeros = symcomp.solve(f, x) -- this is needed for correct indices

    pretty = "The function $" .. fname .. "$"

    if #zeros == 0 then
        pretty = pretty .. " does not have extremal points"
    else
        pretty = pretty .. " has"
    end

    for k, v in pairs(zeros) do
        y = symcomp.evalAt(diff2, x, basic(v))

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

        pretty = pretty .. " at $(" .. latex(v) .. "," .. latex(y) ..")$ because $" .. fname .. "''(" .. requirestringdisplay(x) .. "_" .. k + #fzeros .. ")"

        if tonumber(basic(y)) > 0 then
            pretty = pretty .. " > 0$"
        else -- todo: if == 0 then check inflection
            pretty = pretty .. " < 0$"
        end
    end

    return pretty .. "."
end

-- TODO: move to snippets
function symcomp.printintegral(f, u, l, x)
    return "\\int_{" .. requirestringdisplay(u) .. "}^{" .. requirestringdisplay(l) .. "}{" .. requirestringdisplay(f) .. "}\\,\\mathrm{d}" .. requirestringdisplay(x)    
end

return symcomp