# `wsymcomp.lua`

> the symbolic computation module

## Contents

- [symcomp.evalAt]()
- [symcomp.sub]()
- [symcomp.solve]()
- [symcomp.diff]()
- [symcomp.integrate]()

---

## The common return value

All functions presented herein return a table with a so-called *basic* string at index `1` and a LaTeX representation of that string at index `2`.

### Example

```lua
res = symcomp.expr("1/2*x")

print(res[1]) -- "1/2*x"
print(res[2]) -- "\frac{1}{2} x"
```

---

## `symcomp.evalAt(f, x, x0)` - evaluates `f(x)` at `x=x0`

> `symcomp.evalAt` can be used to evaluate the function `f(x)` at `x=x0`.

### Signature

```lua
res = symcomp.evalAt(f, x, x0)
```

### Example

```lua
f = symcomp.expr("-1/2*x**3")

res = symcomp.evalAt(f, "x", 1)
```

#### Output (`res[1]`):

```ini
-1/2
```

---

## `symcomp.sub(a, b)` - returns `a - b` 

> subtracts `b` from `a` where `a`, `b` can be arbitrary expressions (numbers, polynomials etc.).

### Signature

```lua
res = symcomp.sub(a, b)
```

### Example

```lua
f = symcomp.expr("2*x**4+7*x-3")
g = symcomp.expr("3*x**3-2*x+7")

res = symcomp.sub(f, g)
```

#### Output (`res[1]`)

```ini
2*x**4-3*x**3+9*x-10
```

---

## `symcomp.solve(f, x)` - solves `f(x) == 0`

> returns a collection of values of `x` where `f(x) == 0`.

### Signature

```lua
res = symcomp.solve(f, x)
```

The return value is a collection of tables as described above, e.g. if a function has zeros `-1/2` and `5/2` then the return value will be the following:

```lua
{
    { "-1/2", "-\frac{1}{2}" },
    {  "5/2", "-\frac{5}{2}" },
}
```

### Example

```lua
f = symcomp.expr("x**2-4")

res = symcomp.solve(f, "x")
```

#### Output (`res[1][1]` and `res[2][1]`)

```ini
-2
2
```

---

## `symcomp.diff(f, x)` - evaluates `df/dx`

> differentiates `f` with respect to `x`

### Signature

```lua
res = symcomp.diff(f, x)
```

### Example

```lua
f = symcomp.expr("-1/2*x**3")

res = symcomp.diff(f, "x")
```

#### Output (`res[1]`):

```ini
(-3/2)*x**2
```

---

## `symcomp.integrate(f, x [, l , u])` - integrates `f` from `l` to `u` with respect to `x`

> evaluates the integral of `f` from `l` to `u` with respect to `x`.

> **⚠️ Warning:**<br/>
> As of now, `f` must be a polynomial. Other types of functions can not be evaluated yet.

### Signature

```lua
res = symcomp.integrate(f, x)
res = symcomp.integrate(f, x, l, u)
```

### Example

```lua
f = symcomp.expr("1/3*x^2")
l = 0
u = 3

symcomp.integrate(f, "x")
symcomp.integrate(f, "x", l, u)
```

#### Output

```ini
x^3/9
3
```
