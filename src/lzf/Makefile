
all: libH5Zlzf.so

libH5Zlzf.so: lzf/liblzf.a
	${CC} ${PKG_CFLAGS} ${PKG_CPICFLAGS} -shared H5Zlzf.c $(PKG_CPPFLAGS) \
	-I./lzf/ ./lzf/liblzf.a ${PKG_LDFLAGS} -o libH5Zlzf.so

lzf/liblzf.a:
	$(MAKE) -C lzf

clean:
	rm -f libH5Zlzf.so
	rm -f lzf/liblzf.a
	rm -f lzf/*.o
