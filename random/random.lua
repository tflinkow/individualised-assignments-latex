local random = random or {}

random.MIN_INT = -10
random.MAX_INT = 10
random.MIN_REAL = -1
random.MAX_REAL = 1

-- creates randomised expressions from the specified expression e, replacing characters with values as specified in the supplied factory
function random.create(e, factory)
    assert(type(factory) == "table")

    for _, v in pairs(factory) do
        e = string.gsub(e, v[1], v[2])
    end

    return e
end

-- returns a random table value
function random.oneof(t)
    assert(type(t) == "table")

    return t[math.random(1, #t)]
end

-- returns a random integer between [a, b] or [random.MIN_INT, random.MAX_INT] if no range is specified
function random.integer(a, b)
    return math.random(a or random.MIN_INT, b or random.MAX_INT)
end

-- returns a string representing a random fraction
function random.rational() -- TODO: allow range specification! allow neg. fractions
    local a = random.integer(1, 15)
    local b = random.integer(1, 15)

    -- no need to reduce fractions, symcomp will do that

    if a < b then
        return "" .. a .. "/" .. b
    else
        return "" .. b .. "/" .. a
    end
end

-- returns a random real number
function random.real(a, b)
    local l = a or random.MIN_REAL
    local u = b or random.MAX_REAL

    return l + (u - l) * math.random()
end

-- returns a random line equation mx+b
function random.line(m, b)
    local factory =
    {
        { "m", m or random.rational() },
        { "b", b or random.integer() }
    }

    return random.create("m*x+b", factory)
end

-- returns a random parabola ax^2
function random.parabola(a, b)
    local factory = 
    {
        { "a", a or random.rational() }
    }

    return random.create("a*x^2", factory)
end

-- returns a random polynomial of the specified degree
function random.polynomial(deg)
    local ex = ""

    for i = 0, deg do
        local power = i
        local coeff = random.integer()
        
        if coeff >= 0 then
            ex = ex .. "+"
        end

        ex = ex .. coeff .. "*x^(" .. power .. ")"
    end

    return ex
end

return random
