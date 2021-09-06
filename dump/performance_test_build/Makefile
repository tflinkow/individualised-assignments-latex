main: main.cpp
	g++ -fPIC -shared main.cpp -o main.so -I/usr/include/lua5.3 -I../../symbolic/headers -lstdc++ -lginac -lcln -lsymengine -lgmp -llua5.3

luamain: luamain.tex
	lualatex --shell-escape luamain.tex

sagemain: sagemain.tex
	lualatex sagemain.tex
	sage sagemain.sagetex.sage
	lualatex sagemain.tex

sympymain: sympymain.tex
	lualatex sympymain.tex
	python3 sympymain.sympy
	lualatex sympymain.tex
