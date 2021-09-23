local random = random or {}

random.MIN_INT = -10
random.MAX_INT = 10
random.MIN_REAL = -1
random.MAX_REAL = 1

math.randomseed(os.time())

function random.create(e, factory)
    assert(type(factory) == "table")

    for _, v in pairs(factory) do
        e = string.gsub(e, v[1], v[2])
    end

    return e
end

function random.oneof(t)
    assert(type(t) == "table")

    return t[math.random(1, #t)]
end

function random.integer(a, b)
    return math.random(a or random.MIN_INT, b or random.MAX_INT)
end

function random.rational() -- TODO: allow range specification! allow neg. fractions
    a = random.integer(1, 15)
    b = random.integer(1, 15)

    -- no need to reduce fractions, symcomp will do that

    if a < b then
        return "" .. a .. "/" .. b
    else
        return "" .. b .. "/" .. a
    end
end

function random.real(a, b)
    l = a or random.MIN_REAL
    u = b or random.MAX_REAL

    return l + (u - l) * math.random()
end

function random.line(m, b)
    local factory =
    {
        { "m", m or random.rational() },
        { "b", b or random.integer() }
    }

    return random.create("m*x+b", factory)
end

function random.parabola(a, b)
    local factory = 
    {
        { "a", a or random.rational() }
    }

    return random.create("a*x**2", factory)
end

function random.polynomial(deg)
    local ex = ""

    for i = 0, deg do
        power = i
        coeff = random.integer()
        
        if coeff >= 0 then
            ex = ex .. "+"
        end

        ex = ex .. coeff .. "*x**(" .. power .. ")"
    end

    return ex
end

function newStack()
    return {""}
end

function addString(stack, s)
    table.insert(stack, s)
    
    for i=#stack-1, 1, -1 do
        if string.len(stack[i]) > string.len(stack[i+1]) then
            break
        end
        
        stack[i] = stack[i] .. table.remove(stack)
    end
end

function random.polynomial2(deg)
    local s = newStack()

    for i = 0, deg do
        power = i
        coeff = random.integer()
        
        if coeff >= 0 then
            addString(s, "+")
        end

        addString(s, "*x**(" .. power .. ")")        
    end

    return table.concat(s)
end

return random
