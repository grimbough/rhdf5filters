SHELL=/bin/sh

# To assist in cross-compiling
CC=gcc
CXX=g++
AR=ar
RANLIB=ranlib
LDFLAGS=
CFLAGS=-fPIC -O2
CXXFLAGS=-fPIC -O2

BLOSC_OBJS=	blosc/bitshuffle-avx2.o \
			blosc/blosc.o \
			blosc/shuffle-avx2.o \
			blosc/shuffle-sse2.o \
			blosc/bitshuffle-generic.o \
			blosc/blosclz.o \
			blosc/shuffle.o \
			blosc/bitshuffle-sse2.o \
			blosc/fastcopy.o \
			blosc/shuffle-generic.o

LZ4_OBJS=	internal-complibs/lz4-1.8.3/lz4.o \
		 	internal-complibs/lz4-1.8.3/lz4hc.o

SNAPPY_OBJS=internal-complibs/snappy-1.1.1/snappy.o \
			internal-complibs/snappy-1.1.1/snappy-c.o \
			internal-complibs/snappy-1.1.1/snappy-sinksource.o \
			internal-complibs/snappy-1.1.1/snappy-stubs-internal.o

ZSTD_OBJS=	internal-complibs/zstd-1.3.8/debug.o \
            internal-complibs/zstd-1.3.8/fse_decompress.o \
            internal-complibs/zstd-1.3.8/pool.o \
            internal-complibs/zstd-1.3.8/zstd_compress.o \
            internal-complibs/zstd-1.3.8/zstd_double_fast.o \
            internal-complibs/zstd-1.3.8/zstdmt_compress.o \
			internal-complibs/zstd-1.3.8/entropy_common.o \
			internal-complibs/zstd-1.3.8/hist.o \
			internal-complibs/zstd-1.3.8/threading.o \
			internal-complibs/zstd-1.3.8/zstd_ddict.o \
			internal-complibs/zstd-1.3.8/zstd_fast.o \
			internal-complibs/zstd-1.3.8/zstd_opt.o \
			internal-complibs/zstd-1.3.8/error_private.o \
			internal-complibs/zstd-1.3.8/huf_compress.o \
			internal-complibs/zstd-1.3.8/xxhash.o \
			internal-complibs/zstd-1.3.8/zstd_decompress_block.o \
			internal-complibs/zstd-1.3.8/zstd_lazy.o \
			internal-complibs/zstd-1.3.8/fse_compress.o \
			internal-complibs/zstd-1.3.8/huf_decompress.o \
			internal-complibs/zstd-1.3.8/zstd_common.o \
			internal-complibs/zstd-1.3.8/zstd_decompress.o \
			internal-complibs/zstd-1.3.8/zstd_ldm.o


all: libH5Zblosc.so

libH5Zblosc.so:	libblosc.a
	$(CXX) $(CXXFLAGS) -shared -o libH5Zblosc.so H5Zblosc.c \
			-I/mnt/Storage/R-library/3.6.1/Rhdf5lib/include -I./blosc \
			/home/msmith/Code/PyTables/c-blosc/build/blosc/libblosc.a \
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
	$(MAKE) -C blosc all

SUBDIRS = internal-complibs/snappy-1.1.1 internal-complibs/lz4-1.8.3 internal-complibs/zstd-1.3.8

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@

clean:
	rm -f libH5Zblosc.so
	rm -f libblosc.a
	rm -f blosc/*.o
	rm -f internal-complibs/snappy-1.1.1/*.o
	rm -f internal-complibs/lz4-1.8.3/*.o
	rm -f internal-complibs/zstd-1.3.8/*.o