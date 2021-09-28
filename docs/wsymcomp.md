# `wsymcomp.lua`

> the symbolic computation module

## Contents

- [wsymcomp.evalAt]()
- [wsymcomp.sub]()
- [wsymcomp.solve]()
- [wsymcomp.diff]()
- [wsymcomp.integrate]()

---

## The common return value

All functions presented herein return a table with a so-called *basic* string at index `1` and a LaTeX representation of that string at index `2`.

### Example

```lua
res = wsymcomp.expr("1/2*x")

print(res[1]) -- "1/2*x"
print(res[2]) -- "\frac{1}{2} x"
```

---

## `wsymcomp.evalAt(f, x, x0)` - evaluates `f(x)` at `x=x0`

> `wsymcomp.evalAt` can be used to evaluate the function `f(x)` at `x=x0`.

### Signature

```lua
res = wsymcomp.evalAt(f, x, x0)
```

### Example

```lua
f = wsymcomp.expr("-1/2*x**3")

res = wsymcomp.evalAt(f, "x", 1)
```

#### Output (`res[1]`):

```ini
-1/2
```

---

## `wsymcomp.sub(a, b)` - returns `a - b` 

> subtracts `b` from `a` where `a`, `b` can be arbitrary expressions (numbers, polynomials etc.).

### Signature

```lua
res = wsymcomp.sub(a, b)
```

### Example

```lua
f = wsymcomp.expr("2*x**4+7*x-3")
g = wsymcomp.expr("3*x**3-2*x+7")

res = wsymcomp.sub(f, g)
```

#### Output (`res[1]`)

```ini
2*x**4-3*x**3+9*x-10
```

---

## `wsymcomp.solve(f, x)` - solves `f(x) == 0`

> returns a collection of values of `x` where `f(x) == 0`.

### Signature

```lua
res = wsymcomp.solve(f, x)
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
f = wsymcomp.expr("x**2-4")

res = wsymcomp.solve(f, "x")
```

#### Output (`res[1][1]` and `res[2][1]`)

```ini
-2
2
```

---

## `wsymcomp.diff(f, x)` - evaluates `df/dx`

> differentiates `f` with respect to `x`

### Signature

```lua
res = wsymcomp.diff(f, x)
```

### Example

```lua
f = wsymcomp.expr("-1/2*x**3")

res = wsymcomp.diff(f, "x")
```

#### Output (`res[1]`):

```ini
(-3/2)*x**2
```

---

## `wsymcomp.integrate(f, x [, l , u])` - integrates `f` from `l` to `u` with respect to `x`

> evaluates the integral of `f` from `l` to `u` with respect to `x`.

> **⚠️ Warning:**<br/>
> As of now, `f` must be a polynomial. Other types of functions can not be evaluated yet.

### Signature

```lua
res = wsymcomp.integrate(f, x)
res = wsymcomp.integrate(f, x, l, u)
```

### Example

```lua
f = wsymcomp.expr("1/3*x^2")
l = 0
u = 3

wsymcomp.integrate(f, "x")
wsymcomp.integrate(f, "x", l, u)
```

#### Output (`res[1]`)

```ini
x^3/9
3
```
