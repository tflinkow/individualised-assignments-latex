CPP = g++
CPFLAGS = -fPIC -Wall

ODIR = obj
BDIR = bin

module: main.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	g++ -fPIC -shared main.cpp -o main.so -I/usr/include/lua5.3 -lstdc++ -lginac -lcln -llua5.3
#$(CPP) main.cpp $(CFLAGS) -I/usr/include/lua5.3 -o main.o -lstdc++ -lginac -lcln
#$(CPP) $(CFLAGS) -shared -o main.so main.o -llua5.3

#$(CC) $(CFLAGS) -I$(LUAINCLUDE) -c main.cpp -o $(ODIR)/module.o
#$(CC) $(CFLAGS) -shared -o $(BDIR)/module.so $(ODIR)/module.o -llua5.3

randpoly: randpoly.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	g++ randpoly.cpp -o randpoly -lginac

exvect: exvect.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	g++ exvect.cpp -o exvect -lginac

intg: integral_comparison.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	g++ integral_comparison.cpp -o intg -lginac

report: maintex.tex
	lualatex --shell-escape maintex.tex

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)