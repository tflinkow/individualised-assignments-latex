local random = random or {}

math.randomseed(os.time())

function random.expr(e)
    return actual.expr(e) -- no typecheck here, as actual will do that
end

function random.oneof(t)
    assert(type(t) == "table")

    return t[math.random(1, #t)]
end

return random