local random = random or {}

math.randomseed(os.time())

-- returns a randomized expression, where certain characters are replaced according to the supplied table
function random.create(e, factory)
    assert(type(factory) == "table")

    for _, v in pairs(factory) do
        e = e:gsub(v[1], v[2])
    end

    return e
end

-- returns a parabola ax^2+b with rational a and user-specified b or integer b, if none supplied
function random.parabola(b)
    local factory = 
    {
        { "a", random.rational() },
        { "b", b or random.integer(-6, 7) }
    }

    return random.create("a*x**2+b", factory)
end

-- returns a line mx+b with rational m and user-specified b or integer b, if none supplied
function random.line()
    local factory =
    {
        { "m", random.rational() },
        { "b", b or random.integer(-10, 11) }
    }

    return random.create("m*x+b", factory)
end

-- returns a polynomial with the specified max degree and integer coefficients
function random.polynomial(deg)
    local ex = ""

    for i = 0, deg do
        --power = random.integer(0, i)
        power = i
        coeff = random.integer(-10, 10)
        
        if coeff >= 0 then
            ex = ex .. "+"
        end

        ex = ex .. coeff .. "*x**(" .. power .. ")"
    end

    return ex
end

-- returns a randomly chosen table entry
function random.oneof(t)
    assert(type(t) == "table")

    return t[math.random(1, #t)]
end

-- returns a random float number between [a, b)
function random.real(a, b)
    return a + (b - a) * math.random()
end

-- returns a random rational number between [0, 1]
function random.rational()
    a = random.integer(1, 15)
    b = random.integer(1, 15)

    -- no need to reduce fractions, symcomp will do that

    if a < b then
        return "" .. a .. "/" .. b
    else
        return "" .. b .. "/" .. a
    end
end

-- returns a random integer number between [a, b)
function random.integer(a, b)
    return math.random(a, b)
end

return random