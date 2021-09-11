CPP = g++
CPFLAGS = -std=c++20 -fPIC -shared -Wall -Wextra

BDIR = bin

all: symcomp.cpp exprrep.cpp
	mkdir -p $(BDIR)
	$(CPP) $(CPFLAGS) symcomp.cpp exprrep.cpp -o $(BDIR)/symcomp.so -lstdc++ -lginac -lcln -lsymengine -lgmp -llua5.3

clean: 
	rm -rf $(BDIR)/symcomp.so
#	rm -rf $(BDIR)
