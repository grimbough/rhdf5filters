all: libH5Zbz2.so

libH5Zbz2.so:
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Zbzip2.c $(PKG_CPPFLAGS) \
	-lbz2 ${PKG_LDFLAGS} -o libH5Zbz2.so

clean:
	rm -f libH5Zbz2.so
