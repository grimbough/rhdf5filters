EXTRA_FLAGS+=-I../third_party/streamvbyte/include/ -I../third_party/ -I../../zstd/ -msse3
FLAGS=$(PKG_CXXFLAGS) $(PKG_CXXPICFLAGS) $(PKG_CPPFLAGS) $(EXTRA_FLAGS)

all: vbz.o v0/vbz_streamvbyte.o v1/vbz_streamvbyte.o

vbz.o: vbz.cpp
	$(CXX) $(FLAGS) -c vbz.cpp -o vbz.o
v0/vbz_streamvbyte.o: v0/vbz_streamvbyte.cpp
	$(CXX) $(FLAGS) -c v0/vbz_streamvbyte.cpp -o v0/vbz_streamvbyte.o
v1/vbz_streamvbyte.o: v1/vbz_streamvbyte.cpp
	$(CXX) $(FLAGS) -c v1/vbz_streamvbyte.cpp -o v1/vbz_streamvbyte.o

clean:
	rm -f *.o

