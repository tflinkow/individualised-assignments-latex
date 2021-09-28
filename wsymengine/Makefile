CPP = g++
CPFLAGS = -std=c++20 -fPIC -shared -Wall -Wextra

BDIR = bin

all: wsymengine.cpp exprrep.cpp
	mkdir -p $(BDIR)
	$(CPP) $(CPFLAGS) wsymengine.cpp exprrep.cpp -o $(BDIR)/wsymengine.so -lstdc++ -lsymengine -lgmp -llua5.3

clean: 
	rm -rf $(BDIR)
