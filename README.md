# bachelorthesis

## versions

```
gcc 10.3.0
Lua 5.3 (5.3.3-1)
LuaLaTeX 1.12.0 (TeXLive 2020)
Ubuntu 21.04
```

## env setup

```
# general:
sudo apt-get update
sudo apt-get upgrade -ygitk
sudo apt-get install build-essential -y

sudo apt-get install libmsgsl-dev -y

#SymEngine:
sudo apt-get install cmake libgmp-dev -y
#download using Git
mkdir build && cd build
cmake ..
make
sudo make install
ctest

#GiNaC
sudo apt-install ginac-tools -y
sudo apt-install libginac-dev -y

#TeXLive
sudo apt-get install texlive texlive-latex-extra -y

#Lua
sudo apt-get install lua5.3 -y
sudo apt-get install liblua5.3-dev -y
```

## include locations

```
Lua: usr/include/lua5.3
GiNaC: usr/include/ginac
SymbolicC++: /usr/local/include/
SymEngine: /usr/local/include/symengine
```
