# data_structus

Library with data structures for linux
``` Makefile
CC = gcc
CFLAGS = -g -Werror -Wextra

LIBDIR = PATH TO data_structures/lib
INCDIR = PATH TO data_structures/include

all: main

main: main.c $(LIBDIR)/libdata.so
	$(CC) -o $@ $< -ldata -Wl,-rpath,$(LIBDIR) -L$(LIBDIR) -I$(INCDIR)
```

*AVL trees don't work :(*
