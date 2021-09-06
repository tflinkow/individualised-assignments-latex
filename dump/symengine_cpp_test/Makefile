CPP = g++
CPFLAGS = -Wall

ODIR = obj
BDIR = bin

module: main.cpp
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	$(CPP) main.cpp $(CFLAGS) -o main -lstdc++ -lsymengine -lgmp

#$(CC) $(CFLAGS) -I$(LUAINCLUDE) -c main.cpp -o $(ODIR)/module.o
#$(CC) $(CFLAGS) -shared -o $(BDIR)/module.so $(ODIR)/module.o -llua5.3

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)