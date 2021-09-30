local wsymmath = wsymmath or {}

local util = require "util"
local symmath = require "symmath"

symmath.setup{ implicitVars = true, fixVariableNames = true }
symmath.export.LaTeX.openSymbol = ""
symmath.export.LaTeX.closeSymbol = ""

-- creates a table representing an ExprRep object
function CreateExprRep(ex)
    return { symmath.export.Lua(ex), symmath.export.LaTeX(ex) }
end

-- loads Lua code at run-time
function Load(s)
    return load("return " .. util.strings.CaretExponent(s))()
end

-- integrates the function f with respect to x, optionally within bounds [l, u]
function wsymmath.integrate(f, x, l, u)
    F = Load(f)
    X = Load(x)

    print(l)
    print(u)

    if l == nil and u == nil then
        return CreateExprRep(symmath.Integral(F, X)())
    end

    L = Load(l)
    U = Load(u)

    res = symmath.Integral(F, X, L, U)()

    return CreateExprRep(res)
end

return wsymmath