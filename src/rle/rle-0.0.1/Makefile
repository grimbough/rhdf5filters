FLAGS=$(PKG_CFLAGS) $(PKG_CPICFLAGS)

OBJS= rle.o

all: librle.a 

librle.a: $(OBJS)
	rm -f librle.a
	$(AR) cq librle.a $(OBJS)
	
clean: 
	rm -f *.o librle.a 

rle.o: rle.c
	$(CC) $(FLAGS) -c rle.c

