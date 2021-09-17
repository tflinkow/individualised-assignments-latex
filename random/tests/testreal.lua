package.path = package.path .. ";../../wsymcomp/?.lua;../?.lua"
package.cpath = package.cpath .. ";../../symcomp/bin/?.so"

local random = require "random"

print(random.real())