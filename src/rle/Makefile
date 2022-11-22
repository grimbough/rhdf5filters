
all: libH5Zrle.so libH5Zturborle.so

libH5Zrle.so: rle-0.0.1/librle.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Zrle.c $(PKG_CPPFLAGS) \
	-I./rle-0.0.1/ ./rle-0.0.1/librle.a ${PKG_LDFLAGS} -o libH5Zrle.so
	
libH5Zturborle.so: Turbo-Run-Length-Encoding/libtrle.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Ztrle.c $(PKG_CPPFLAGS) \
	-I/Turbo-Run-Length-Encoding/ ./Turbo-Run-Length-Encoding/libtrle.a ${PKG_LDFLAGS} -o libH5Zturborle.so

rle-0.0.1/librle.a:
	$(MAKE) -C rle-0.0.1
	
Turbo-Run-Length-Encoding/libtrle.a:
	$(MAKE) -C Turbo-Run-Length-Encoding
	
clean:
	rm -f libH5Zrle.so
	rm -f rle-0.0.1/librle.a
	rm -f rle-0.0.1/*.o
	rm -f libH5Zturborle.so
	rm -f Turbo-Run-Length-Encoding/libtrle.a
	rm -f Turbo-Run-Length-Encoding/*.o

