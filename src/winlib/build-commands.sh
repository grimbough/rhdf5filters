
CC=/c/Rtools/mingw_32/bin/gcc.exe
CXX=/c/Rtools/mingw_32/bin/g++.exe
RHDF5_INCLUDE=/c/Users/Mike/DOCUME~1/R/WIN-LI~1/3.4/Rhdf5lib/include/
RHDF5_LIBS="-L/c/Users/Mike/Documents/R/win-library/3.4/Rhdf5lib/lib/i386/"

cd /c/Users/Mike/Code/github/hdf5Filters/src/blosc/lib/lz4-r119
${CC} -c *.c
cd ../snappy-1.1.1
${CXX} ${CXXFLAGS} -c *.cc
cd ../blosc-1.4.1
${CC} ${CFLAGS} -I../lz4-r119/ -I../snappy-1.1.1/ -c *.c
cd ../../
${CC} -I${RHDF5_INCLUDE} -I./lib/blosc-1.4.1/ -c H5Zblosc.c
## Linking step
${CXX} -shared \
    -I${RHDF5_INCLUDE} -I./lib/blosc-1.4.1/ -o libh5blosc.dll \
    H5Zblosc.o lib/blosc-1.4.1/*.o lib/lz4-r119/*.o lib/snappy-1.1.1/*.o \
    ${RHDF5_LIBS} -lhdf5 -lszip -lz -lstdc++
mv libh5blosc.dll ../winlib/i386/

	
	
CC=/c/Rtools/mingw_64/bin/gcc.exe
CXX=/c/Rtools/mingw_64/bin/g++.exe
RHDF5_INCLUDE=/c/Users/Mike/DOCUME~1/R/WIN-LI~1/3.4/Rhdf5lib/include/
RHDF5_LIBS="-L/c/Users/Mike/Documents/R/win-library/3.4/Rhdf5lib/lib/x64/"

cd /c/Users/Mike/Code/github/hdf5Filters/src/blosc/lib/lz4-r119
${CC} -c *.c
cd ../snappy-1.1.1
${CXX} ${CXXFLAGS} -c *.cc
cd ../blosc-1.4.1
${CC} ${CFLAGS} -I../lz4-r119/ -I../snappy-1.1.1/ -c *.c
cd ../../
${CC} -I${RHDF5_INCLUDE} -I./lib/blosc-1.4.1/ -c H5Zblosc.c
## Linking step
${CXX} -shared \
    -I${RHDF5_INCLUDE} -I./lib/blosc-1.4.1/ -o libh5blosc.dll \
    H5Zblosc.o lib/blosc-1.4.1/*.o lib/lz4-r119/*.o lib/snappy-1.1.1/*.o \
    ${RHDF5_LIBS} -lhdf5 -lszip -lz -lstdc++
mv libh5blosc.dll ../winlib/x64/




CC=/c/Rtools/mingw_32/bin/gcc.exe
RHDF5_INCLUDE="$HOME/DOCUME~1/R/WIN-LI~1/3.4/Rhdf5lib/include/"
RHDF5_LIBS="-L$HOME/Documents/R/win-library/3.4/Rhdf5lib/lib/i386/"

cd "$HOME/Code/github/hdf5Filters/src/lzf"
${CC} -I"${RHDF5_INCLUDE}" "${RHDF5_LIBS}" -shared lib/*.c lzf_filter.c \
  "$HOME/Code/bioconductor/Rhdf5lib/src/winlib/i386/hdf5.dll" \
  "$HOME/Code/bioconductor/Rhdf5lib/src/winlib/i386/szip.dll" -lz -o liblzf_filter.dll
mv liblzf_filter.dll ../winlib/i386/



CC=/c/Rtools/mingw_64/bin/gcc.exe
RHDF5_INCLUDE="$HOME/DOCUME~1/R/WIN-LI~1/3.4/Rhdf5lib/include/"
RHDF5_LIBS="-L$HOME/Documents/R/win-library/3.4/Rhdf5lib/lib/x64/"

cd "$HOME/Code/github/hdf5Filters/src/lzf"
${CC} -I"${RHDF5_INCLUDE}" "${RHDF5_LIBS}" -shared lib/*.c lzf_filter.c \
  "$HOME/Code/bioconductor/Rhdf5lib/src/winlib/x64/hdf5.dll" \
  "$HOME/Code/bioconductor/Rhdf5lib/src/winlib/x64/szip.dll" -lz -o liblzf_filter.dll
mv liblzf_filter.dll ../winlib/x64/
