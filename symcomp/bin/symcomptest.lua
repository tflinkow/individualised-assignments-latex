local symcomp = require "symcomp"

-- todo: should these go to a .sty file??
function basic(t)
    return t[1]
end

function latex(t)
    return t[2]
end
    
f = symcomp.expression("1/2*x^2")
g = symcomp.expression("x+4")
    
result = symcomp.derivate(basic(f), "x")

print(latex(f))
print(latex(result))

--print(latex(symcomp.evaluateAt(basic(g), "x", 4)))

-- calculate intersection points
res = symcomp.solve("1/2*x^2-(x+4)", "x")
print(#res) -- number of intersections

first = res[1]
print(latex(first))

second = res[2]
print(latex(second))