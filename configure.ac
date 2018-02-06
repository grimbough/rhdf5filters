# Process this file with autoconf to produce a configure script.
# author: Mike Smith (mike.smith@embl.de)

AC_PREREQ([2.65])
AC_INIT([hdf5Filters], [0.0.1], [grimbough@gmail.com])
AC_CONFIG_SRCDIR([src])

# Check the compiler configured with R
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CXX=`"${R_HOME}/bin/R" CMD config CXX`
CXXFLAGS=`"${R_HOME}/bin/R" CMD config CXXFLAGS`
MAKE=`"${R_HOME}/bin/R" CMD config MAKE`

# Checks for programs.
AC_PROG_CC

# determine the location of the Rhdf5lib versions of the HDF5 library
RHDF5_LIBS=`echo 'Rhdf5lib::pkgconfig("PKG_C_DYNAMIC_LIBS")'|\
    "${R_HOME}/bin/R" --vanilla --slave`
RHDF5_INCLUDE=`echo 'cat(system.file("include", package="Rhdf5lib"))'|\
    "${R_HOME}/bin/R" --vanilla --slave`
    
echo $RHDF5_INCLUDE

echo "building the LZF filter...";
cd src/lzf
${CC} -I${RHDF5_INCLUDE} -fPIC -shared lib/*.c lzf_filter.c $RHDF5_LIBS -o liblzf_filter.so
cd ../../

echo "building the LZ4 filter...";
## build LZ4 filter
cd src/lz4/lib;
make
cd ../
${CC} ${CLFAGS} -fPIC -shared -w -I$RHDF5_INCLUDE H5Zlz4.c lib/liblz4.a $RHDF5_LIBS  -o libH5Zlz4.so
cd ../../

echo `pwd`

echo "building the BLOSC filter...";
cd src/blosc/lib/lz4-r119
${CC} ${CFLAGS} -fPIC -c *.c
cd ../snappy-1.1.1
${CXX} ${CXXFLAGS} -fPIC -c *.cc
cd ../blosc-1.4.1
${CC} ${CFLAGS} -fPIC -I../lz4-r119/ -I../snappy-1.1.1/ -c *.c
cd ../../
${CC} ${CFLAGS} -fPIC -I${RHDF5_INCLUDE} -I./lib/blosc-1.4.1/ -c H5Zblosc.c
## Linking step
${CXX} ${CXXFLAGS} -fPIC -shared \
    -I${RHDF5_INCLUDE} -I./lib/blosc-1.4.1/ \
    -o libh5blosc.so \
    H5Zblosc.o lib/blosc-1.4.1/*.o lib/lz4-r119/*.o lib/snappy-1.1.1/*.o \
    ${RHDF5_LIBS} -lz -lpthread
cd ../../


#update variables in Makevars
HDF5_INCLUDE="${BASEPBNAME}/src"
AC_SUBST(HDF5_INCLUDE)
AC_MSG_NOTICE([   HDF5_INCLUDE=${HDF5_INCLUDE}])

LZF_LIB="lzf/liblzf_filter.so"
LZ4_LIB="lz4/libH5Zlz4.so"
BLOSC_LIB="blosc/libh5blosc.so"

AC_SUBST(LZF_LIB)
AC_SUBST(LZ4_LIB)
AC_SUBST(BLOSC_LIB)
AC_MSG_NOTICE([   LZF_LIB=${LZF_LIB}])
AC_MSG_NOTICE([   LZ4_LIB=${LZ4_LIB}])
AC_MSG_NOTICE([   BLOSC_LIB=${BLOSC_LIB}])
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
