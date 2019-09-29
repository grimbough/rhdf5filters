SHELL=/bin/sh

# To assist in cross-compiling
CC=gcc
AR=ar
RANLIB=ranlib
LDFLAGS=


CPPFLAGS+= -I. -I./common -DXXH_NAMESPACE=ZSTD_
DEBUGFLAGS= -Wall -Wextra -Wcast-qual -Wcast-align -Wshadow \
            -Wstrict-aliasing=1 -Wswitch-enum -Wdeclaration-after-statement \
            -Wstrict-prototypes -Wundef -Wpointer-arith -Wformat-security \
            -Wvla -Wformat=2 -Winit-self -Wfloat-equal -Wwrite-strings \
            -Wredundant-decls -Wmissing-prototypes -Wc++-compat
CFLAGS  += $(DEBUGFLAGS) $(MOREFLAGS)
FLAGS    = $(CPPFLAGS) $(CFLAGS)

ZSTDCOMMON_FILES := $(sort $(wildcard common/*.c))
ZSTDCOMP_FILES := $(sort $(wildcard compress/*.c))
ZSTDDECOMP_FILES := $(sort $(wildcard decompress/*.c))
ZSTD_FILES := $(ZSTDCOMMON_FILES) $(ZSTDCOMP_FILES) $(ZSTDDECOMP_FILES)

ZSTD_OBJ   := $(patsubst %.c,%.o,$(ZSTD_FILES))

.PHONY: all clean 

all: $(ZSTD_FILES)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^

clean:
	@$(RM) *.o common/*.o compress/*.o decompress/*.o 


