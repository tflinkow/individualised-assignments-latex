CPP = g++
CPFLAGS = -fPIC -Wall

ODIR = obj
BDIR = bin

intg: integral_comparison.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	g++ integral_comparison.cpp -I./ -o intg -lginac

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)