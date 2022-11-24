CC=gcc
FLAGS=-fPIC -msse4.1 -mavx

OBJS= rle128_extreme_cpu.o  \
      rle24_extreme_cpu.o    \
      rle48_extreme_cpu.o   \
      rle8_cpu.o  \
      rle8_extreme_cpu.o   \
      rle8_extreme_mmtf.o \
      rle8_ocl.o \
      rle8_ultra_cpu.o \
      rleX_extreme_cpu.o \
      rle_mmtf.o \
      rle_sh.o

all: librle8.a

librle8.a: $(OBJS)
	rm -f librle8.a
	ar cq librle8.a $(OBJS)

rle128_extreme_cpu.o: rle128_extreme_cpu.c
	$(CC) $(FLAGS) -c rle128_extreme_cpu.c
rle24_extreme_cpu.o: rle24_extreme_cpu.c
	$(CC) $(FLAGS) -c rle24_extreme_cpu.c
rle48_extreme_cpu.o: rle48_extreme_cpu.c
	$(CC) $(FLAGS) -c rle48_extreme_cpu.c
rle8_cpu.o: rle8_cpu.c
	$(CC) $(FLAGS) -c rle8_cpu.c
rle8_extreme_cpu.o: rle8_extreme_cpu.c
	$(CC) $(FLAGS) -c rle8_extreme_cpu.c
rle8_extreme_mmtf.o: rle8_extreme_mmtf.c
	$(CC) $(FLAGS) -c rle8_extreme_mmtf.c
rle8_ocl.o: rle8_ocl.c
	$(CC) $(FLAGS) -c rle8_ocl.c
rle8_ultra_cpu.o: rle8_ultra_cpu.c
	$(CC) $(FLAGS) -c rle8_ultra_cpu.c
rleX_extreme_cpu.o: rleX_extreme_cpu.c
	$(CC) $(FLAGS) -c rleX_extreme_cpu.c
rle_mmtf.o: rle_mmtf.c
	$(CC) $(FLAGS) -c rle_mmtf.c
rle_sh.o: rle_sh.c
	$(CC) $(FLAGS) -c rle_sh.c

clean:
	rm *.o
	rm librle8.a
