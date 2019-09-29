SHELL=/bin/sh

# To assist in cross-compiling
CC=gcc
CXX=g++
AR=ar
RANLIB=ranlib
LDFLAGS=
CFLAGS=-fPIC -O2
CXXFLAGS=-fPIC -O2

SNAPPY_OBJS=snappy.o \
			snappy-c.o \
			snappy-sinksource.o \
			snappy-stubs-internal.o


all: $(SNAPPY_OBJS)

snappy.o: snappy.cc
	$(CXX) $(CXXFLAGS) -c snappy.cc
snappy-c.o: snappy-c.cc
	$(CXX) $(CXXFLAGS) -c snappy-c.cc
snappy-sinksource.o: snappy-sinksource.cc
	$(CXX) $(CXXFLAGS) -c snappy-sinksource.cc
snappy-stubs-internal.o: snappy-stubs-internal.cc
	$(CXX) $(CXXFLAGS) -c snappy-stubs-internal.cc

clean:
	rm -f *.o