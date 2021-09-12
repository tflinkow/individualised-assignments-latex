local symcomp = require "symcomp"

-- todo: should these go to a .sty file??
function basic(t)
    return t[1]
end

function latex(t)
    return t[2]
end
    
f = symcomp.expr("1/2*x^2")
g = symcomp.expr("x+4")
    
result = symcomp.diff(basic(f), "x")

print(latex(f))
print(latex(result))

-- calculate intersection points
res = symcomp.solve("1/2*x^2-(x+4)", "x")
print(#res) -- number of intersections

firstx = res[1]
firsty = symcomp.evalAt(basic(f), "x", tonumber(basic(firstx))) -- todo: tonumber is ugly af

secondx = res[2]
secondy = symcomp.evalAt(basic(f), "x", tonumber(basic(secondx)))

--integrate between intersection points
lim1 = tonumber(basic(firstx))
lim2 = tonumber(basic(secondx))

if lim1 < lim2 then
    lower = lim1
    upper = lim2
else
    lower = lim2
    upper = lim1
end

sub = symcomp.sub(basic(g), basic(f))
print(basic(sub))
res = symcomp.integrate(basic(sub), lower, upper, "x")
print(latex(res))
