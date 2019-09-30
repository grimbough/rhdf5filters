SHELL=/bin/sh

# To assist in cross-compiling
CC=gcc
AR=ar
RANLIB=ranlib
LDFLAGS=
CPPFLAGS+=-I. -I./common -DXXH_NAMESPACE=ZSTD_
CFLAGS  +=-fPIC $(DEBUGFLAGS)
FLAGS    = $(CPPFLAGS) $(CFLAGS)

ZSTDCOMMON_FILES := $(sort $(wildcard common/*.c))
ZSTDCOMP_FILES := $(sort $(wildcard compress/*.c))
ZSTDDECOMP_FILES := $(sort $(wildcard decompress/*.c))
ZSTD_FILES := $(ZSTDCOMMON_FILES) $(ZSTDCOMP_FILES) $(ZSTDDECOMP_FILES)

ZSTD_OBJ   := $(patsubst %.c,%.o,$(ZSTD_FILES))

.PHONY: clean 

all: $(ZSTD_OBJ)

debug.o: common/debug.c
	cd common && $(CC) $(FLAGS) -c debug.c
error_private.o: common/error_private.c
	cd common && $(CC) $(FLAGS) -c error_private.c
pool.o: common/pool.c
	cd common && $(CC) $(FLAGS) -c pool.c
xxhash.o: common/xxhash.c
	cd common && $(CC) $(FLAGS) -c xxhash.c
entropy_common.o: common/entropy_common.c
	cd common && $(CC) $(FLAGS) -c entropy_common.c
fse_decompress.o: common/fse_decompress.c
	cd common && $(CC) $(FLAGS) -c fse_decompress.c
threading.o: common/threading.c
	cd common && $(CC) $(FLAGS) -c threading.c
zstd_common.o: common/zstd_common.c
	cd common && $(CC) $(FLAGS) -c zstd_common.c

fse_compress.o: compress/fse_compress.c
	cd compress && $(CC) $(FLAGS) -c fse_compress.c
huf_compress.o: compress/huf_compress.c
	cd compress && $(CC) $(FLAGS) -c huf_compress.c
zstd_double_fast.o: compress/zstd_double_fast.c
	cd compress && $(CC) $(FLAGS) -c zstd_double_fast.c
zstd_lazy.o: compress/zstd_lazy.c
	cd compress && $(CC) $(FLAGS) -c zstd_lazy.c
zstdmt_compress.o: compress/zstdmt_compress.c
	cd compress && $(CC) $(FLAGS) -c zstdmt_compress.c
hist.o: compress/hist.c
	cd compress && $(CC) $(FLAGS) -c hist.c
zstd_compress.o: compress/zstd_compress.c
	cd compress && $(CC) $(FLAGS) -c zstd_compress.c
zstd_fast.o: compress/zstd_fast.c
	cd compress && $(CC) $(FLAGS) -c zstd_fast.c
zstd_ldm.o: compress/zstd_ldm.c
	cd compress && $(CC) $(FLAGS) -c zstd_ldm.c
zstd_opt.o: compress/zstd_opt.c	
	cd compress && $(CC) $(FLAGS) -c zstd_opt.c

huf_decompress.o: decompress/huf_decompress.c
	cd decompress && $(CC) $(FLAGS) -c huf_decompress.c
zstd_ddict.o: decompress/zstd_ddict.c
	cd decompress && $(CC) $(FLAGS) -c zstd_ddict.c
zstd_decompress_block.o: decompress/zstd_decompress_block.c
	cd decompress && $(CC) $(FLAGS) -c zstd_decompress_block.c
zstd_decompress.o: decompress/zstd_decompress.c
	cd decompress && $(CC) $(FLAGS) -c zstd_decompress.c


clean:
	@$(RM) *.o common/*.o compress/*.o decompress/*.o 


