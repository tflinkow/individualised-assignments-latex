local util = util or {}

util.strings = {}

-- returns a Lua number from a string which represents a fraction as num/denum
function util.strings.FractionToNumber(s)
    -- turn '-1/2' into (-1) divided by (2) etc.
    idx = s:find("/")
    return tonumber(s:sub(1, idx - 1)) / tonumber(s:sub(idx + 1, #s))
end

-- returns an expression where the symbol for exponentiation is ^
function util.strings.CaretExponent(s)
    -- turns x**2+3*x to x^2+3*x
    return s:gsub("%*%*", "^")
end

-- returns an expression where the symbol for exponentiation is **
function util.strings.AstExponent(s)
    -- turns x^2+3*x to x**2+3*x
    return s:gsub("%^", "**")
end

-- provides functions that deal with tables representing an ExprRep (ExpressionRepresentation) object
util.exprrep = {}

-- returns the basic form of an ExprRep object
function util.exprrep.Basic(e)
    return e[1]
end

-- returns the basic form of an ExprRep object
function util.exprrep.LaTeX(e)
    return e[2]
end

-- flexible way to get a string from x if x is a string or a table representing an ExprRep object
function util.BasicStringFromAny(x)
    if type(x) == "string" then
        return x
    elseif type(x) == "table" then
        if #x == 2 then
            return util.exprrep.Basic(x)
        else
            error("TODO")
        end
    elseif type(x) == "number" then
        return tostring(x) -- TODO??
    else
        return x -- in case x is nil
    end
end

-- flexible way to get a LaTeX string from x if x is a string or a table representing an ExprRep object
function util.LaTeXStringFromAny(x)
    if type(x) == "string" then
        return x
    elseif type(x) == "table" then
        if #x == 2 then
            return util.exprrep.LaTeX(x)
        else
            error("TODO")
        end
    elseif type(x) == "number" then
        return tostring(x) -- TODO??
    else
        return x -- in case x is nil
    end
end

-- flexible way to get a number from x if x is a string or a table representing an ExprRep object
function util.NumberFromAny(x)
    if type(x) == "string" then
        if x:find("/") then
            return util.strings.FractionToNumber(x)
        else
            return tonumber(x)
        end
    elseif type(x) == "table" then
        if #x == 2 then
            return tonumber(util.exprrep.Basic(x))
        else
            error("TODO")
        end
    elseif type(x) == "number" then
        return x
    else
        return x -- in case x is nil
    end
end

return util