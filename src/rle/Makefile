
all: libH5Zrle.so

libH5Zrle.so: rle-0.0.1/librle.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Zrle.c $(PKG_CPPFLAGS) \
	-I./rle-0.0.1/ ./rle-0.0.1/librle.a ${PKG_LDFLAGS} -o libH5Zrle.so

rle-0.0.1/librle.a:
	$(MAKE) -C rle-0.0.1

clean:
	rm -f libH5Zrle.so
	rm -f rle-0.0.1/librle.a
	rm -f rle-0.0.1/*.o
