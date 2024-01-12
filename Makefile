GCC = gcc
CFLAGS = -Wall -g

INCDIR   = $(PWD)/include
LIBDIR   = $(PWD)/lib
SRCDIR   = $(PWD)/src

CFILES = $(wildcard $(SRCDIR)/*.c)
HFILES = $(wildcard $(INCDIR)/*.h)

all: main

# Stores .so in lib folder and access from there using,
# -Wl,-rpath,$(LIBDIR)
$(LIBDIR)/libdata.so: $(CFILES) $(HFILES) 
	$(GCC) $(CFLAGS) -shared -fPIC -o $@ $^

main: main.c $(LIBDIR)/libdata.so
	$(GCC) $(CFLAGS) -o main $< -ldata -Wl,-rpath,$(LIBDIR) -L$(LIBDIR) -I$(INCDIR)

clean:
	rm main

# Another way to do this is to store the .so file in the system library.
# then you can omit -Wl,-rpath,$(LIBDIR)
# Also the system library depends on your linux system. RED HAT => usr/lib64
# /usr/lib64/libdata.so: $(CFILES) $(HFILES) 
# 	sudo $(GCC) $(CFLAGS) $(SOFLAGS) -o $@ $^
# 	sudo ldconfig

# main: main.c /usr/lib64/libdata.so
# 	$(GCC) $(CFLAGS) -o main $< -ldata -L$(LIBDIR) -I$(INCDIR)





