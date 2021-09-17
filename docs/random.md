# `random.lua`

> the randomization module

## Contents

- [Constants]()
- [random.create]()
- [random.oneof]()
- [random.integer]()
- [random.rational]()
- [random.real]()
- [random.line]()
- [random.parabola]()
- [random.polynomial]()

---

## Module Constants

The randomisation module provides the following constants which are used in `random.integer()` and `random.real()` if the user does not specify upper and lower bounds.

```lua
random.MIN_INT = -10
random.MAX_INT = 10
random.MIN_REAL = -1
random.MAX_REAL = 1
```

---

## `random.create()` - create any randomized expression

> `random.create` can be used to create any mathematical expression with user-specified constraints on parameters.

### Signature

```lua
s = random.create(e, t)
```

### Example

```lua
local factory =
{
    { "a", random.rational() },
    { "n", random.integer(2, 5) },
    { "b", random.oneof(4, 6, 10) }
}

e = random.create("a*x**n+b", factory)
```

#### Output:

```ini
1/2*x**2+6
5/7*x**3+4
9/10*x**4+10
2/3*x**3+4
```

### Errors

- `e` is not a string or is `nil`
- `t` is not a table, is empty or is `nil`

---

## `random.oneof(t)` - randomly choose one of the supplied values

### Signature

```lua
v = random.oneof(t)
```

### Example

```lua
v = random.oneof({ "1/2*x", "2/3*x", "1/4*x" })
```

#### Output:

```ini
1/2*x
1/4*x
```

## Errors

- `t` is not a table

---

## `random.integer([a [, b]])` - random integer

### Signature

```lua
number = random.integer()
number = random.integer(a)
number = random.integer(a, b)
```

Parameters `a` and `b` are optional.

- `a` and `b` specified -> return value will be in `[a, b)`
- `a` specified -> return value will be in `[a, random.MAX_INT)`
- none specified -> return value will be in `[random.MIN_INT, random.MAX_INT)`

## Errors

- `a` is not a number
- `b` is not a number

---

## `random.rational()` - random rational number

> returns a string that represents a rational number between `[0, 1]` as a fraction

### Signature

```lua
s = random.rational()
```

---

## `random.real([a [, b]])` - random floating-point number

### Signature

```lua
number = random.real()
number = random.real(a)
number = random.real(a, b)
```

Parameters `a` and `b` are optional.

- `a` and `b` specified -> return value will be in `[a, b)`
- `a` specified -> return value will be in `[a, random.MAX_REAL)`
- none specified -> return value will be in `[random.MIN_REAL, random.MAX_REAL)`

## Errors

- `a` is not a number
- `b` is not a number

---

## `random.line([m [, b]])` - random line equation

> returns a string representing the line `m*x+b`

### Signature

```lua
s = random.line()
s = random.line(m)
```

Parameters `m` (slope) and `b` (y-intersect) are optional.

- `m` specified -> y-intersect will be `random.integer()`
- none specified -> slope will be `random.rational()` and `y`-intersect will be `random.integer()`

### Example

```lua
s = random.line()
```

#### Output:

```ini
3*x+4
7*x+2
```

---

## `random.parabola([a])` - random parabola

> returns a string representing the parabola `a*x^2`

### Signature

```lua
s = random.parabola()
s = random.parabola(a)
```

Parameter `a` is optional.

- not specified -> `a` will be `random.rational()`

### Example

```lua
s = random.parabola()
```

#### Output:

```ini
1/2*x**2
3/5*x**2
```

---

## `random.polynomial(deg)` - random polynomial

> returns a string representing a polynomial of degree `deg`

### Signature

```lua
s = random.polynomial(deg)
```

Parameter `deg` specifies the highest possible exponent. The created polynomial does not necessarily have a term with that power, because the coefficient can be `0`.

### Example

```lua
s = random.polynomial(5)
```

#### Output:

```ini
4+7*x-2*x**3+5*x**4
3*x**2+8*x**5
```