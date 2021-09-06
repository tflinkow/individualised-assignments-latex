CC = gcc
CFLAGS = -fPIC -Wall

ODIR = obj
BDIR = bin

LUAINCLUDE = /usr/include/lua5.3

module: main.c
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)
	$(CC) $(CFLAGS) -I$(LUAINCLUDE) -c main.c -o $(ODIR)/module.o
	$(CC) $(CFLAGS) -shared -o $(BDIR)/module.so $(ODIR)/module.o -llua5.3

clean:
	rm -rf $(ODIR)
	rm -rf $(BDIR)