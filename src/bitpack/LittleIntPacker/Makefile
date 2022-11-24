FLAGS=$(PKG_CFLAGS) $(PKG_CPICFLAGS)

LIP_LIB=liblip.a

HEADERS=include/bitpacking.h  include/portability.h include/util.h

OBJECTS2= bmipacking32.o bitpacking32.o util.o turbobitpacking32.o scpacking32.o horizontalpacking32.o

all: $(LIP_LIB) $(OBJECTS2)

liblip.a: $(OBJECTS2)
	$(AR) cq liblip.a $(OBJECTS2)

bmipacking32.o: ./src/bmipacking32.c $(HEADERS)
	$(CC) $(FLAGS) -mavx -c ./src/bmipacking32.c -Iinclude

horizontalpacking32.o: ./src/horizontalpacking32.c $(HEADERS)
	$(CC) $(FLAGS) -c ./src/horizontalpacking32.c -Iinclude

turbobitpacking32.o: ./src/turbobitpacking32.c $(HEADERS)
	$(CC) $(FLAGS) -c ./src/turbobitpacking32.c -Iinclude
scpacking32.o: ./src/scpacking32.c $(HEADERS)
	$(CC) $(FLAGS) -c ./src/scpacking32.c -Iinclude



bitpacking32.o: ./src/bitpacking32.c $(HEADERS)
	$(CC) $(FLAGS) -c ./src/bitpacking32.c -Iinclude

util.o: ./src/util.c $(HEADERS)
	$(CC) $(FLAGS) -c ./src/util.c -Iinclude

clean:
	rm -f $(OBJECTS2) $(LIP_LIB)
