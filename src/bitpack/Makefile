all: libH5Zlip.so libH5Zsimdcomp.so

libH5Zlip.so: LittleIntPacker/liblip.a H5Zlip.c
	$(CC) $(PKG_CFLAGS) $(PKG_CPICFLAGS) -shared H5Zlip.c $(PKG_CPPFLAGS) \
	-I./LittleIntPacker/include ./LittleIntPacker/liblip.a $(PKG_LDFLAGS) -o libH5Zlip.so
	
libH5Zsimdcomp.so: simdcomp/libsimdcomp.a H5Zsimdcomp.c
	$(CC) $(PKG_CFLAGS) $(PKG_CPICFLAGS) -shared H5Zsimdcomp.c $(PKG_CPPFLAGS) \
	-I./simdcomp/include ./simdcomp/libsimdcomp.a $(PKG_LDFLAGS) -o libH5Zsimdcomp.so

LittleIntPacker/liblip.a:
	$(MAKE) -C LittleIntPacker
	
simdcomp/libsimdcomp.a:
	$(MAKE) -C simdcomp

clean:
	$(MAKE) -C LittleIntPacker clean
	$(MAKE) -C simdcomp clean
	rm -f *.o libH5Zlip.so libH5Zsimdcomp.so
