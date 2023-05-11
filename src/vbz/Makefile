STREAMVBYTE_OBJS=	third_party/streamvbyte/streamvbyte_0124_decode.o \
					third_party/streamvbyte/streamvbyte_0124_encode.o \
					third_party/streamvbyte/streamvbyte_decode.o \
					third_party/streamvbyte/streamvbyte_encode.o \
					third_party/streamvbyte/streamvbytedelta_decode.o \
					third_party/streamvbyte/streamvbytedelta_encode.o \
					third_party/streamvbyte/streamvbyte_zigzag.o

all: libH5Zvbz.so

libH5Zvbz.so: libvbz.a
	$(CXX) $(PKG_CXXFLAGS) $(PKG_CXXPICFLAGS) $(PKG_CPPFLAGS) -shared vbz_plugin.cpp \
	libvbz.a $(PKG_LDFLAGS) ../zstd/libzstd.a third_party/streamvbyte/libstreamvbyte.a -o libH5Zvbz.so

libvbz.a: vbz
	rm -f libvbz.a
	$(AR) cq libvbz.a vbz/vbz.o vbz/v0/vbz_streamvbyte.o vbz/v1/vbz_streamvbyte.o
	ranlib libvbz.a

.PHONY: vbz

vbz: streamvbyte
	$(MAKE) -C vbz

.PHONY: streamvbyte

streamvbyte:
	$(MAKE) -C third_party/streamvbyte

clean:
	rm -f *.o libH5Zvbz.so
	rm -f vbz/*.o vbz/v0/*.o vbz/v1/*.o vbz/libvbz.a
	rm -f third_party/streamvbyte/*.o third_party/streamvbyte/libstreamvbyte.a
