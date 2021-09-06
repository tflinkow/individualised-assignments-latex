CPP = g++
CPFLAGS = -fPIC -Wall

ODIR = obj
BDIR = bin

main: main.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	g++ main.cpp -o main -I../../symbolic/headers/

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)