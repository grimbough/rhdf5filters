SHELL=/bin/sh

export CC
export CFLAGS
export CPICFLAGS
export CXX
export CXXFLAGS
export CXXPICFLAGS	
export CPPFLAGS
export MAKE
export AR

BLOSC_OBJS=	lib/blosc-1.16.3/bitshuffle-avx2.o \
			lib/blosc-1.16.3/blosc.o \
			lib/blosc-1.16.3/shuffle-avx2.o \
			lib/blosc-1.16.3/shuffle-sse2.o \
			lib/blosc-1.16.3/bitshuffle-generic.o \
			lib/blosc-1.16.3/blosclz.o \
			lib/blosc-1.16.3/shuffle.o \
			lib/blosc-1.16.3/bitshuffle-sse2.o \
			lib/blosc-1.16.3/fastcopy.o \
			lib/blosc-1.16.3/shuffle-generic.o

LZ4_OBJS=	lib/lz4-1.8.3/lz4.o \
		 	lib/lz4-1.8.3/lz4hc.o

SNAPPY_OBJS=lib/snappy-1.1.1/snappy.o \
			lib/snappy-1.1.1/snappy-c.o \
			lib/snappy-1.1.1/snappy-sinksource.o \
			lib/snappy-1.1.1/snappy-stubs-internal.o

ZSTDCOMMON_FILES := $(sort $(wildcard lib/zstd-1.3.8/common/*.c))
ZSTDCOMP_FILES := $(sort $(wildcard lib/zstd-1.3.8/compress/*.c))
ZSTDDECOMP_FILES := $(sort $(wildcard lib/zstd-1.3.8/decompress/*.c))
ZSTD_FILES := $(ZSTDCOMMON_FILES) $(ZSTDCOMP_FILES) $(ZSTDDECOMP_FILES)
ZSTD_OBJS   := $(patsubst %.c,%.o,$(ZSTD_FILES))


all: libH5Zblosc.so

libH5Zblosc.so:	libblosc.a
	$(CXX) $(CXXFLAGS) $(CPICFLAGS) -shared -o libH5Zblosc.so H5Zblosc.c \
			$(CPPFLAGS) -I./lib/blosc-1.16.3 \
			libblosc.a \
			-lpthread -lz

libblosc.a:  blosc
	rm -f libblosc.a
	$(AR) cq libblosc.a $(BLOSC_OBJS) $(SNAPPY_OBJS) $(LZ4_OBJS) $(ZSTD_OBJS)
	@if ( test -f $(RANLIB) -o -f /usr/bin/ranlib -o \
		-f /bin/ranlib -o -f /usr/ccs/bin/ranlib ) ; then \
		echo $(RANLIB) libblosc.a ; \
		$(RANLIB) libblosc.a ; \
	fi

.PHONY: blosc

blosc: subdirs
	$(MAKE) -C lib/blosc-1.16.3 all

SUBDIRS = lib/snappy-1.1.1 lib/lz4-1.8.3 lib/zstd-1.3.8

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@

clean:
	rm -f libH5Zblosc.so
	rm -f libblosc.a
	rm -f lib/blosc-1.16.3/*.o
	rm -f lib/snappy-1.1.1/*.o
	rm -f lib/lz4-1.8.3/*.o
	$(MAKE) -C lib/zstd-1.3.8/ clean