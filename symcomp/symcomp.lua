local symcomp = symcomp or {}

local util = require "util"
local wsymengine = require "wsymengine"
local wsymmath = require "wsymmath"

-- creates a table representing a mathematical expression as an ExprRep object
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

-- subtracts b from a (hence a - b)
function symcomp.sub(a, b)
    return wsymengine.sub(util.BasicStringFromAny(a), util.BasicStringFromAny(b))
end

-- TODO: it would be good to be able to typecheck, and have only one sub method

-- subtracts the matrix B from A (hence A - B)
function symcomp.matrixSub(A, B)
    return wsymengine.matrixSub(util.BasicStringFromAny(A), util.BasicStringFromAny(B))
end

-- solves f(x) == 0
function symcomp.solve(f, x)
    -- SymEngine's solve method has weird bugs, see https://github.com/symengine/symengine/issues/1843
    return wsymengine.solve(util.BasicStringFromAny(f), util.BasicStringFromAny(x))
end

-- integrates f with respect to x from l to u, l and u optional
function symcomp.integrate(f, x, l, u)
    return wsymmath.integrate(util.BasicStringFromAny(f), util.BasicStringFromAny(x), util.BasicStringFromAny(l), util.BasicStringFromAny(u))
end

-- returns the identity matrix of the specified size
function symcomp.identityMatrix(n)
    return wsymengine.identityMatrix(util.NumberFromAny(n))
end

-- creates a matrix from an expression of the form [a11, a12, ..., a1n] [a21, a22, ..., a2n] ... [am1, am2, ..., amn]
function symcomp.matrix(m)
    return wsymengine.matrix(util.BasicStringFromAny(m))
end

-- returns s * m where s is a scalar and m a matrix
function symcomp.scalarMul(s, m)
    return wsymengine.scalarMul(util.BasicStringFromAny(s), util.BasicStringFromAny(m))
end

-- calculates the determinant of the specified matrix
function symcomp.det(m) -- TODO: where check for square?? or does SymEngine check
    return wsymengine.det(util.BasicStringFromAny(m))
end

-- returns the eigenvalues of the specified matrix
function symcomp.eigenvalues(m)
    return wsymengine.eigenvalues(util.BasicStringFromAny(m))
end

-- returns a string which can be used by LaTeX
function symcomp.getstringlatex(x)
    return util.LaTeXStringFromAny(x)
end

-- returns a string that can be used by TikZ/PGFplots
function symcomp.getstringpgf(x)
    return util.strings.CaretExponent(util.BasicStringFromAny(x))
end

-- finds the points of intersections between f and g
function symcomp.findintersections(f, g, x)
    local h = symcomp.sub(f, g)
    
    local intersections = symcomp.solve(h, x)

    return intersections
end

-- returns a string which lists the points of intersections
function symcomp.printintersections(f, g, x)
    local h = symcomp.sub(f, g)
    local intersections = symcomp.solve(h, x)

    local pretty = ""

    if #intersections == 0 then
        pretty = pretty .. "The functions do not intersect"
    else
        pretty = pretty .. "The functions intersect at "
    end

    for k, v in pairs(intersections) do
        -- f or g does not matter, f(x0)=g(x0) where x0 is intersection
        y = symcomp.evalAt(f, x, util.exprrep.Basic(v))

        if k == 1 then
        
        elseif k == #intersections then
            pretty = pretty .. " and at "
        else
            pretty = pretty .. ", "
        end

        pretty = pretty .. "$P_" .. k .. "(" .. util.exprrep.LaTeX(v) .. "," .. util.exprrep.LaTeX(y) .. ")^T$"
    end

    return pretty .. "."
end

-- returns a string which lists the zeros of a function
function symcomp.printzeros(f, fname, x, startidx) -- startidx opt
    startidx = startidx or 0

    local zeros = symcomp.solve(f, x)

    local pretty = "The function $" .. fname .. "$"

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

        pretty = pretty .. "$" .. util.LaTeXStringFromAny(x) .. "_" .. k + startidx .. "=" .. util.exprrep.LaTeX(v) .. "$"
    end

    return pretty .. "."
end

-- returns a string listing the minimums and maximums of a function
function symcomp.printminmax(f, fname, x)
    local diff1 = symcomp.diff(f, x)
    local diff2 = symcomp.diff(diff1, x)
    local zeros = symcomp.solve(diff1, x)

    local fzeros = symcomp.solve(f, x) -- this is needed for correct indices

    local pretty = "The function $" .. fname .. "$"

    if #zeros == 0 then
        pretty = pretty .. " does not have extremal points"
    else
        pretty = pretty .. " has"
    end

    for k, v in pairs(zeros) do
        local val = symcomp.evalAt(diff2, x, util.exprrep.Basic(v))
        local y = symcomp.evalAt(f, x, util.exprrep.Basic(v))

        if k == 1 then
        
        elseif k == #zeros then
            pretty = pretty .. " and"
        else
            pretty = pretty .. ","
        end

        if tonumber(util.exprrep.Basic(val)) > 0 then
            pretty = pretty .. " a minimum"
        else -- todo: if == 0 then check inflection
            pretty = pretty .. " a maximum"
        end

        pretty = pretty .. " at $(" .. util.exprrep.LaTeX(v) .. "," .. util.exprrep.LaTeX(y) ..")$ because $" .. fname .. "''(" .. util.LaTeXStringFromAny(x) .. "_" .. k + #fzeros .. ")"

        if tonumber(util.exprrep.Basic(val)) > 0 then
            pretty = pretty .. " > 0$"
        else -- todo: if == 0 then check inflection
            pretty = pretty .. " < 0$"
        end
    end

    return pretty .. "."
end

-- returns a string which contains the integral specified
function symcomp.printintegral(f, u, l, x)
    if u == nil and l == nil then
        return "\\int{" .. util.LaTeXStringFromAny(f) .. "}\\,\\mathrm{d}" .. util.LaTeXStringFromAny(x)        
    else
        return "\\int_{" .. util.LaTeXStringFromAny(u) .. "}^{" .. util.LaTeXStringFromAny(l) .. "}{" .. util.LaTeXStringFromAny(f) .. "}\\,\\mathrm{d}" .. util.LaTeXStringFromAny(x)    
    end
end

-- returns a string which lists the eigenvalues of a matrix
function symcomp.printeigenvalues(A, Aname, startidx) -- startidx opt
    startidx = startidx or 0

    local eigenvalues = symcomp.eigenvalues(A)

    local pretty = "The matrix $" .. Aname .. "$"

    if #eigenvalues == 0 then
        pretty = pretty .. " does not have eigenvalues"
    elseif #eigenvalues == 1 then
        pretty = pretty .. " has the eigenvalue "
    else
        pretty = pretty .. " has the eigenvalues "
    end

    for k, v in pairs(eigenvalues) do
        if k == 1 then
        
        elseif k == #eigenvalues then
            pretty = pretty .. " and "
        else
            pretty = pretty .. ", "
        end

        pretty = pretty .. "$\\lambda_" .. k + startidx .. "=" .. util.exprrep.LaTeX(v) .. "$"
    end

    return pretty .. "."
end

return symcomp
