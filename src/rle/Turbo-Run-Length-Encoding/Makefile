FLAGS=-fPIC

all: libtrle.a

libtrle.a: trlec.o trled.o
	rm -f libtrle.a
	$(AR) cq libtrle.a trlec.o trled.o

trlec.o: trlec.c
	$(CC) $(FLAGS) -c trlec.c
trled.o: trled.c
	$(CC) $(FLAGS) -c trled.c

clean:
	rm -f *.o libtrle.a