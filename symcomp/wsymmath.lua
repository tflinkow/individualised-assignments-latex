local wsymmath = wsymmath or {}

local util = require "util"
local symmath = require "symmath"

symmath.setup{ implicitVars = true, fixVariableNames = true }
symmath.export.LaTeX.openSymbol = ""
symmath.export.LaTeX.closeSymbol = ""

function CreateExprRep(ex)
    return { symmath.export.Lua(ex), symmath.export.LaTeX(ex) }
end

function Load(s)
    return load("return " .. util.strings.CaretExponent(s))()
end

function wsymmath.diff(f, x)
    newF = Load(f)
    newX = Load(x)

    res = symmath.Derivative(newF, newX)()

    return CreateExprRep(res)
end

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