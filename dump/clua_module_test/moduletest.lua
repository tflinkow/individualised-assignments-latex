package.cpath = package.cpath .. ";./bin/?.so"

local mathmodule = require 'module'

-- mathmodule has the two functions "add" and "theAnswer"
print(mathmodule.add(10, 20))
print(mathmodule.theAnswer())

-- and we registered one global function "globalFunction" too
print(globalFunction())