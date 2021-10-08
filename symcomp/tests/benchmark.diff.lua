package.path = package.path .. ";../?.lua"
package.cpath = package.cpath .. ";../wsymengine/bin/?.so"

local wsymengine = require "wsymengine"
local wsymmath = require "wsymmath"

-- wsymengine.diff
local f = "7*x^4+3*x^3-8*x^2+4*x-10"

local iterations = 1e6

local time = os.clock()

for i=1,iterations do 
    local _ = wsymengine.diff(f, "x")
end

local result = os.clock() - time

print("wsymengine took " .. result .. " s for " .. iterations .. " iterations (" .. result / iterations .. " s pro call)")

time = os.clock()

for i=1,iterations do 
    local _ = wsymmath.diff(f, "x")
end

result = os.clock() - time

print("wsymmath took " .. result .. " s for " .. iterations .. " iterations (" .. result / iterations .. " s pro call)")