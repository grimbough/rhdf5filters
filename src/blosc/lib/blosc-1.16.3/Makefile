SHELL=/bin/sh

EXTRA_FLAGS+=-I../lz4-1.8.3 -I../snappy-1.1.1 -I../zstd-1.3.8
FLAGS=$(CFLAGS) $(CPICFLAGS) $(CPPFLAGS) $(EXTRA_FLAGS)

BLOSC_FILES := $(sort $(wildcard *.c))
BLOSC_OBJS  := $(patsubst %.c,%.o,$(BLOSC_FILES))

all: $(BLOSC_OBJS)

bitshuffle-avx2.o: bitshuffle-avx2.c
	$(CC) $(FLAGS) -mavx2 -c bitshuffle-avx2.c
blosc.o: blosc.c
	$(CC) $(FLAGS) -c blosc.c
shuffle-avx2.o: shuffle-avx2.c
	$(CC) $(FLAGS) -mavx2 -c shuffle-avx2.c
shuffle-sse2.o: shuffle-sse2.c
	$(CC) $(FLAGS) -msse2 -c shuffle-sse2.c
bitshuffle-generic.o: bitshuffle-generic.c
	$(CC) $(FLAGS) -c bitshuffle-generic.c
blosclz.o: blosclz.c
	$(CC) $(FLAGS) -c blosclz.c
shuffle.o: shuffle.c
	$(CC) $(FLAGS) -c shuffle.c
bitshuffle-sse2.o: bitshuffle-sse2.c
	$(CC) $(FLAGS) -msse2 -c bitshuffle-sse2.c
fastcopy.o: fastcopy.c
	$(CC) $(FLAGS) -c fastcopy.c
shuffle-generic.o: shuffle-generic.c
	$(CC) $(FLAGS) -c shuffle-generic.c
			
clean:
	rm -f *.o