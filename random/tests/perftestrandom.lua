package.path = package.path .. ";../../wsymcomp/?.lua;../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local random = require "random"
local symcomp = require "symcomp"

start = os.clock()

for i=1, 1000000 do
    random.polynomial(15)
end

print("Lua: " .. os.clock() - start)

start = os.clock()

for i=1, 1000000 do
    symcomp.debug_randompolynomial(15)
end

print("C++: " .. os.clock() - start)