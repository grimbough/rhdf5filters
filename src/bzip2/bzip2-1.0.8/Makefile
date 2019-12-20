# ------------------------------------------------------------------
# This file is part of bzip2/libbzip2, a program and library for
# lossless, block-sorting data compression.
#
# bzip2/libbzip2 version 1.0.8 of 13 July 2019
# Copyright (C) 1996-2019 Julian Seward <jseward@acm.org>
#
# Please read the WARNING, DISCLAIMER and PATENTS sections in the 
# README file.
#
# This program is released under the terms of the license contained
# in the file LICENSE.
# ------------------------------------------------------------------

BIGFILES=-D_FILE_OFFSET_BITS=64
FLAGS=$(PKG_CFLAGS) $(PKG_CPICFLAGS) $(BIGFILES)


OBJS= blocksort.o  \
      huffman.o    \
      crctable.o   \
      randtable.o  \
      compress.o   \
      decompress.o \
      bzlib.o

all: libbz2.a 

libbz2.a: $(OBJS)
	rm -f libbz2.a
	$(AR) cq libbz2.a $(OBJS)
	@if ( test -f $(RANLIB) -o -f /usr/bin/ranlib -o \
		-f /bin/ranlib -o -f /usr/ccs/bin/ranlib ) ; then \
		echo $(RANLIB) libbz2.a ; \
		$(RANLIB) libbz2.a ; \
	fi

clean: 
	rm -f *.o libbz2.a 

blocksort.o: blocksort.c
	$(CC) $(FLAGS) -c blocksort.c
huffman.o: huffman.c
	$(CC) $(FLAGS) -c huffman.c
crctable.o: crctable.c
	$(CC) $(FLAGS) -c crctable.c
randtable.o: randtable.c
	$(CC) $(FLAGS) -c randtable.c
compress.o: compress.c
	$(CC) $(FLAGS) -c compress.c
decompress.o: decompress.c
	$(CC) $(FLAGS) -c decompress.c
bzlib.o: bzlib.c
	$(CC) $(FLAGS) -c bzlib.c
bzip2.o: bzip2.c
	$(CC) $(FLAGS) -c bzip2.c
bzip2recover.o: bzip2recover.c
	$(CC) $(FLAGS) -c bzip2recover.c

