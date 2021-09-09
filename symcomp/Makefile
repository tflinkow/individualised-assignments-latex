CPP = g++
CPFLAGS = -fPIC -shared -Wall

BDIR = bin

symcomp: symcomp.cpp
	mkdir -p $(BDIR)
	$(CPP) $(CPFLAGS) symcomp.cpp -o $(BDIR)/symcomp.so -lstdc++ -lginac -lcln -lsymengine -lgmp -llua5.3

clean: 
	rm -rf $(BDIR)
