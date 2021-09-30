CPP = g++
CPFLAGS = -std=c++20 -Wall -Wextra
LINK = -lstdc++ -lsymengine -lgmp -llua5.3

BDIR = bin

all: wsymengine.cpp exprrep.cpp
	mkdir -p $(BDIR)
	$(CPP) $(CPFLAGS) -fPIC -shared wsymengine.cpp exprrep.cpp -o $(BDIR)/wsymengine.so $(LINK)
	
tests: tests.cpp
	mkdir -p $(BDIR)
	$(CPP) $(CPFLAGS) tests.cpp exprrep.cpp -o $(BDIR)/tests $(LINK)

clean: 
	rm -rf $(BDIR)
