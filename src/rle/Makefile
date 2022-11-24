
all: libH5Zrle.so libH5Zturborle.so libH5Zrle8.so

libH5Zrle.so: rle-0.0.1/librle.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Zrle.c $(PKG_CPPFLAGS) \
	-I./rle-0.0.1/ ./rle-0.0.1/librle.a ${PKG_LDFLAGS} -o libH5Zrle.so
	
libH5Zrle8.so: rle8/librle8.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Zrle8.c $(PKG_CPPFLAGS) \
	-I./rle8/ ./rle8/librle8.a ${PKG_LDFLAGS} -o libH5Zrle8.so	
	
libH5Zturborle.so: Turbo-Run-Length-Encoding/libtrle.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Ztrle.c $(PKG_CPPFLAGS) \
	-I/Turbo-Run-Length-Encoding/ ./Turbo-Run-Length-Encoding/libtrle.a ${PKG_LDFLAGS} -o libH5Zturborle.so

rle-0.0.1/librle.a:
	$(MAKE) -C rle-0.0.1
	
rle8/librle8.a:
	$(MAKE) -C rle8
	
Turbo-Run-Length-Encoding/libtrle.a:
	$(MAKE) -C Turbo-Run-Length-Encoding
	
clean:
	rm -f *.so
	rm -f rle-0.0.1/librle.a
	rm -f rle-0.0.1/*.o
	rm -f Turbo-Run-Length-Encoding/libtrle.a
	rm -f Turbo-Run-Length-Encoding/*.o
	rm -f rle8/librle8.a
	rm -f rle8/*.o

