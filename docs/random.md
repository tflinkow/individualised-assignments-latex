# `random.lua`

> randomization module

## Contents

- [random.create]()
- [random.oneof]()
- [random.integer]()
- [random.rational]()
- [random.real]()
- [random.line]()
- [random.parabola]()
- [random.polynomial]()

## `random.create()` - any randomized expression

> `random.create` can be used to create any mathematical expression with user-specified constraints on parameters.

### Signature

```lua
<string> = random.create(<string>, <table of tables>)
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

#### Example outputs:

```ini
1/2*x**2+6
5/7*x**3+4
9/10*x**4+10
2/3*x**3+4
```

## `random.oneof(t)` - randomly choose one of the supplied values

> `todo`

## Signature

```lua
<string> = random.oneof(<table>)
```

### Example

```lua
e = random.oneof({ "1/2*x", "2/3*x", "1/4*x" })
```

#### Example outputs:

```ini
1/2*x
1/4*x
1/2*x
2/3*x
```

## `random.integer(a, b)` - random integer in `[a, b)`

> `todo`

## Signature

```lua
<number> = random.integer(<number>, <number>)
```

### Example

```lua
e = random.integer(-2, 5)
```

#### Example outputs:

```ini
-2
0
1
4
```