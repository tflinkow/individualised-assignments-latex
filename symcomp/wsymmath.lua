local wsymmath = wsymmath or {}

local util = require "util"
local symmath = require "symmath"

symmath.setup{ implicitVars = true, fixVariableNames = true }
symmath.export.LaTeX.openSymbol = ""
symmath.export.LaTeX.closeSymbol = ""
symmath.tostring = symmath.export.SingleLine

-- creates a table representing an ExprRep object
function wsymmath.CreateExprRep(ex)
    return { symmath.export.SingleLine(ex), symmath.export.LaTeX(ex) }
end

-- loads Lua code at run-time
function Load(s)
    return load("return " .. util.strings.CaretExponent(s))()
end

-- simplifies the expression
function wsymmath.simplify(ex)
    return util.BasicStringFromAny(ex):simplify()
end

-- integrates the function f with respect to x, optionally within bounds [l, u]
function wsymmath.integrate(f, x, l, u)
    local F = Load(f)
    local X = Load(x)

    if l == nil and u == nil then
        return wsymmath.CreateExprRep(symmath.Integral(F, X)())
    else
        L = Load(l)
        U = Load(u)

        return wsymmath.CreateExprRep(symmath.Integral(F, X, L, U)())
    end
end

-- not to be used by symcomp, but rather only for benchmarks
function wsymmath.diff(f, x)
    local F = Load(f)
    local X = Load(x)

    return wsymmath.CreateExprRep(symmath.diff(F, X))
end

return wsymmath