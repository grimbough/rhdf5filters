
FLAGS=$(PKG_CFLAGS) $(PKG_CPICFLAGS)

all: liblzf.a

liblzf.a: lzf_c.o lzf_d.o
	rm -f liblzf.a
	$(AR) cq liblzf.a lzf_c.o lzf_d.o

lzf_c.o: lzf_c.c
	$(CC) $(FLAGS) -c lzf_c.c
lzf_d.o: lzf_d.c
	$(CC) $(FLAGS) -c lzf_d.c

clean:
	rm -f *.o liblzf.a
