# Individualised assignments in LaTeX

This project is a framework to create individualised assignments for mathematics in LaTeX.

It is part of my bachelor's project at the Hochschule Ruhr West University of Applied Sciences and was created from August to October 2021.
The bachelor's thesis itself is [report.pdf](TODO).

# Prerequisites

The following libraries have to be present on your system.

- [SymEngine](https://github.com/symengine/symengine) (a standalone C++ symbolic manipulation library)
- [Symbolic Lua](https://github.com/thenumbernine/symmath-lua) (a computer algebra system written in Lua)
- [Guidelines Support Library](https://github.com/microsoft/GSL) (in combination with the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines))
- [doctest](https://github.com/onqtam/doctest) (C++ testing framework)

The framework was developed and compiled on Ubuntu 21.04 using

- Lua 5.3
- LuaLaTeX 1.12.0 (from TeX Live 2020)

# Features

The framework consists of a randomisation module (documented [here](TODO)) and one module for symbolic computation (documented [here](TODO)).

In addition to that, there are some example tasks in `/taskpool` and there is a main `document.tex` that includes exercises from the task pool, along with a script `create.sh` which can be used to create individualised versions of the document.

Executing the `create.sh` script as follows

```bash
./create.sh document list.csv
```

will create individualised versions of `document.tex` for each line present in the `list.csv` file. 

The `.csv` file can be exported from the e-learning platform moodle. It has to adhere to the following format:

```
[[id]],FirstName,LastName,MatriculationNumber
```

The individualised `.pdf` files will be present in the `/output` folder and will be named `MatriculationNumber_FirstName_LastName_document.pdf`.

# License

(c) Thomas Flinkow 2021

Distributed under the MIT license. See [`LICENSE`](TODO) for more information.
