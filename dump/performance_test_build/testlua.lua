local math = require "main"

-- BASICS
--                         -m  -(m-1)    -1
-- r1, r2, ... , rn = func(p1, p2, ... , pm)
-- -n  -(n-1)    -1

-- [-2] : expr
-- [-1] : symvar
res = math.derivate("3*x^2+7*x+sin(x)", "x")

print(res[1])
print(res[2])

-- [-4] : expr
-- [-3] : llim
-- [-2] : ulim
-- [-1] : symvar
res = math.integrate("3*x^2+7+sqrt(x)", -10, 0.5, "x")

print(res[1])
print(res[2])