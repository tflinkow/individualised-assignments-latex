local symcomp = require "symcomp"

basic, latex = symcomp.expression("3x^4+7/(sin(x^2))")

print(latex)

basic, latex = symcomp.derivate(basic, "x")

print(basic)
print(latex)