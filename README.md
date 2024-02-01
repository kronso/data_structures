# data_structus

Library with data structures for linux
``` console
main: main.c $(LIBDIR)/libdata.so
	@$(GCC) $(CFLAGS) -o main $< -ldata -Wl,-rpath,$(LIBDIR) -L$(LIBDIR) -I$(INCDIR)
```

*AVL trees don't work :(*
