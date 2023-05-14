dnl Process this file with autoconf to produce a configure script.
dnl author: Mike Smith (grimbough@gmail.com)

AC_PREREQ([2.65])
AC_INIT([hdf5Filters], [0.99.3], [grimbough@gmail.com])
AC_CONFIG_SRCDIR([src])

m4_include([tools/ax_gcc_x86_cpu_supports.m4])
m4_include([tools/ax_check_compile_flag.m4])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

AC_SUBST(CC, `"${R_HOME}/bin/R" CMD config CC`)
AC_SUBST(CFLAGS, `"${R_HOME}/bin/R" CMD config CFLAGS`)
AC_SUBST(CPICFLAGS, `"${R_HOME}/bin/R" CMD config CPICFLAGS`)
AC_SUBST(CXX, `"${R_HOME}/bin/R" CMD config CXX`)
AC_SUBST(CXXFLAGS, `"${R_HOME}/bin/R" CMD config CXXFLAGS`)
AC_SUBST(CXXPICFLAGS, `"${R_HOME}/bin/R" CMD config CXXPICFLAGS`)
AC_SUBST(CPPFLAGS, `"${R_HOME}/bin/R" CMD config CPPFLAGS`)
AC_SUBST(MAKE, `"${R_HOME}/bin/R" CMD config MAKE`)
AC_SUBST(RANLIB, `"${R_HOME}/bin/R" CMD config RANLIB`)
AC_SUBST(LDFLAGS, `"${R_HOME}/bin/R" CMD config LDFLAGS`)

## seems unreliable as to whether this information is available
AR=`"${R_HOME}/bin/R" CMD config AR`
AS_IF([test "x$AR" = "xERROR: no information for variable 'AR'"], [AC_PATH_PROG([AR], [ar])], [])
AC_SUBST(AR)

## determine the location of the Rhdf5lib versions of the HDF5 library
RHDF5_INCLUDE=`"${R_HOME}/bin${R_ARCH_BIN}/Rscript" -e 'cat(system.file("include", package="Rhdf5lib"))' | \
    tail -n1`
AC_SUBST(RHDF5_INCLUDE)

##############################
echo "configuring BZIP2 filter..."

HAVE_BZ2="yes"
AC_CHECK_HEADERS([bzlib.h], [HAVE_BZ2_H="yes"], [unset HAVE_BZ2])
if test "x$HAVE_BZ2" = "xyes" -a "x$HAVE_BZ2_H" = "xyes"; then
  AC_CHECK_LIB([bz2], [BZ2_bzDecompressInit],, [unset HAVE_BZ2])
fi
  
dnl if there's not a system install of bzip2 build our own version
if test -z "$HAVE_BZ2"; then
  AC_SUBST(BUILD_BZ2, bzip2-1.0.8/libbz2.a)
  AC_SUBST(BZ2_INCLUDE, -Ibzip2-1.0.8)
  AC_SUBST(BZ2_LIB, bzip2-1.0.8/libbz2.a)
else
  AC_SUBST(BUILD_BZ2, "")
  AC_SUBST(BZ2_INCLUDE, "")
  AC_SUBST(BZ2_LIB, -lbz2)
fi

AC_SUBST(BUILD_BZ2)
AC_SUBST(BZ2_INCLUDE)
AC_SUBST(BZ2_LIB)

AC_CONFIG_FILES([src/bzip2/Makefile])
AC_OUTPUT

##############################
echo "configuring the Zstd filter..."

HAVE_ZSTD="yes"
AC_CHECK_HEADERS([zstd.h], [HAVE_ZSTD_H="yes"], [unset HAVE_ZSTD])
if test "x$HAVE_ZSTD" = "xyes" -a "x$HAVE_ZSTD_H" = "xyes"; then
  AC_CHECK_LIB([zstd], [ZSTD_decompress],, [unset HAVE_ZSTD])
fi

if test -z "$HAVE_ZSTD"; then
  AC_SUBST(BUILD_ZSTD, libzstd.a)
  AC_SUBST(ZSTD_INCLUDE, -I. -Icommon)
  AC_SUBST(ZSTD_LIB, libzstd.a)
else
  AC_SUBST(BUILD_ZSTD, "")
  AC_SUBST(ZSTD_INCLUDE, "")
  AC_SUBST(ZSTD_LIB, -lzstd)
fi

AC_SUBST(BUILD_ZSTD)
AC_SUBST(ZSTD_INCLUDE)
AC_SUBST(ZSTD_LIB)

AC_CONFIG_FILES([src/zstd/Makefile])

##############################
echo "configuring the BLOSC filter..."

HAVE_BLOSC="yes"
AC_CHECK_HEADERS([blosc.h], [HAVE_BLOSC_H="yes"], [unset HAVE_BLOSC])
if test "x$HAVE_BLOSC" = "xyes" -a "x$HAVE_BLOSC_H" = "xyes"; then
  AC_CHECK_LIB([blosc], [blosc_compress],, [unset HAVE_BLOSC])
fi

dnl if there's not a system install of blosc build our own version

if test -z "$HAVE_BLOSC"; then

  ## check if we have an x86 CPU
  machine=`uname -m`
  AS_CASE([$machine],
    [*86*], [x86_CPU=true],
    [x86_CPU=false]
  )
  echo x86_CPU="$x86_CPU"
  
  ## see if -msse2 is a supported flag
  AX_CHECK_COMPILE_FLAG([-msse2], [MSSE2=true], [MSSE2=false])
  ## see if -mavx2 is a supported flag
  AX_CHECK_COMPILE_FLAG([-mavx2], [MAVX2=true], [MAVX2=false])
  
  AC_RUN_IFELSE(
        [AC_LANG_PROGRAM([#include <stdlib.h>],
          [__builtin_cpu_init ();])
        ],
        [ax_cv_gcc_check_x86_cpu_init=true],
        [ax_cv_gcc_check_x86_cpu_init=false])
  
  ## check CPU supports sse2 and avx2
  if [ "$x86_CPU" == true ] && [ "$ax_cv_gcc_check_x86_cpu_init" == true ]; then
      AX_GCC_X86_CPU_SUPPORTS(sse2, [SSE2_SUPPORTED=true], [SSE2_SUPPORTED=false])
      AX_GCC_X86_CPU_SUPPORTS(avx2, [AVX2_SUPPORTED=true], [AVX2_SUPPORTED=false])
  else
      SSE2_SUPPORTED=false
      AVX2_SUPPORTED=false
  fi
  
  if [ "$MSSE2" = true ] && [ "$SSE2_SUPPORTED" = true ] ; then
    SSE2="-DSHUFFLE_SSE2_ENABLED"
    MSSE2="-msse2"
    SSE2_BITSHUFFLE='bitshuffle-sse2.o: bitshuffle-sse2.c
	$(CC) $(FLAGS) -c bitshuffle-sse2.c'
    SSE2_BITSHUFFLE_OBJ='bitshuffle-sse2.o'
    SSE2_SHUFFLE='shuffle-sse2.o: shuffle-sse2.c
	$(CC) $(FLAGS) -c shuffle-sse2.c'
    SSE2_SHUFFLE_OBJ='shuffle-sse2.o'
    SSE2_OBJ_PATH='lib/blosc-1.20.1/'
  else
    SSE2=""
    MSSE2=""
    SSE2_BITSHUFFLE=""
    SSE2_SHUFFLE=""
    SSE2_BITSHUFFLE_OBJ=""
    SSE2_SHUFFLE_OBJ=""
    SSE2_OBJ_PATH=""
  fi
  
  AC_SUBST(SSE2)
  AC_SUBST(MSSE2)
  AC_SUBST(SSE2_BITSHUFFLE)
  AC_SUBST(SSE2_SHUFFLE)
  AC_SUBST(SSE2_BITSHUFFLE_OBJ)
  AC_SUBST(SSE2_SHUFFLE_OBJ)
  AC_SUBST(SSE2_OBJ_PATH)
  
  if [ "$MAVX2" = true ] && [ "$AVX2_SUPPORTED" = true ] ; then
    AVX2="-DSHUFFLE_AVX2_ENABLED"
    MAVX2="-mavx2"
    AVX2_BITSHUFFLE='bitshuffle-avx2.o: bitshuffle-avx2.c
	$(CC) $(FLAGS) -c bitshuffle-avx2.c'
    AVX2_BITSHUFFLE_OBJ='bitshuffle-avx2.o'
    AVX2_SHUFFLE='shuffle-avx2.o: shuffle-avx2.c
	$(CC) $(FLAGS) -c shuffle-avx2.c'
    AVX2_SHUFFLE_OBJ='shuffle-avx2.o'
    AVX2_OBJ_PATH='lib/blosc-1.20.1/'
  else
    AVX2=""
    MAVX2=""
    AVX2_BITSHUFFLE=""
    AVX2_SHUFFLE=""
    AVX2_BITSHUFFLE_OBJ=""
    AVX2_SHUFFLE_OBJ=""
    AVX2_OBJ_PATH=""
  fi
  
  AC_SUBST(AVX2)
  AC_SUBST(MAVX2)
  AC_SUBST(AVX2_BITSHUFFLE)
  AC_SUBST(AVX2_SHUFFLE)
  AC_SUBST(AVX2_BITSHUFFLE_OBJ)
  AC_SUBST(AVX2_SHUFFLE_OBJ)
  AC_SUBST(AVX2_OBJ_PATH)
  
  AC_SUBST(BUILD_BLOSC, "H5Zblosc.o")
  AC_SUBST(BLOSC_INCLUDE, "-I./lib/blosc-1.20.1")
  AC_SUBST(BLOSC_LIB, "./libblosc.a")
else
  AC_SUBST(BUILD_BLOSC, "")
  AC_SUBST(BLOSC_INCLUDE, "")
  AC_SUBST(BLOSC_LIB, -lblosc)
fi

AC_CONFIG_FILES([src/blosc/lib/blosc-1.20.1/Makefile src/blosc/Makefile])

dnl update variables in Makevars
BZIP2_F_LIB="bzip2/libH5Zbz2.so"
BLOSC_F_LIB="blosc/libH5Zblosc.so"
LZF_F_LIB="lzf/libH5Zlzf.so"
#VBZ_LIB="vbz/libH5Zvbz.so"
ZSTD_F_LIB="zstd/libH5Zzstd.so"

AC_SUBST(BZIP2_F_LIB)
AC_SUBST(BLOSC_F_LIB)
AC_SUBST(LZF_F_LIB)
#AC_SUBST(VBZ_LIB)
AC_SUBST(ZSTD_F_LIB)
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
