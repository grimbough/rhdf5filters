
all: libH5Zbz2.so

libH5Zbz2.so:	bzip2-1.0.8/libbz2.a
	${CC} ${CFLAGS} ${CPICFLAGS} -shared H5Zbzip2.c -I$RHDF5_INCLUDE \
	-I./bzip2-1.0.8/ ./bzip2-1.0.8/libbz2.a -o libH5Zbz2.so

bzip2-1.0.8/libbz2.a:
	$(MAKE) -C bzip2-1.0.8

clean:
	rm -f libH5Zbz2.so
	rm -f bzip2-1.0.8/libbz2.a
	rm -f bzip2-1.0.8/*.o
