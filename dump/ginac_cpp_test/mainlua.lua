package.cpath = package.cpath .. ";./?.so;"

local math = require "main"

int, res = math.integral("-1/2*x^2+x+4", -2, 4)

print(int)
print(res)
