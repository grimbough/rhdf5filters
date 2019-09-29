SHELL=/bin/sh

# To assist in cross-compiling
CC=gcc
AR=ar
RANLIB=ranlib
LDFLAGS=
CFLAGS=-fPIC -O2

LZ4_OBJS=	lz4.o \
		 	lz4hc.o

all: $(LZ4_OBJS)

lz4.o: lz4.c lz4.h
	$(CC) $(CFLAGS) -c lz4.c
lz4hc.o: lz4hc.c lz4hc.h lz4.c
	$(CC) $(CFLAGS) -c lz4hc.c

clean:
	rm -f *.o