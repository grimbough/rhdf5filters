# Process this file with autoconf to produce a configure script.
# author: Mike Smith (mike.smith@embl.de)

AC_PREREQ([2.65])
AC_INIT([hdf5Filters], [0.0.1], [grimbough@gmail.com])
AC_CONFIG_SRCDIR([src])

m4_include([tools/ax_gcc_x86_cpu_supports.m4])

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
AC_SUBST(MAKE, `"${R_HOME}/bin/R" CMD config MAKE`)
AC_SUBST(RANLIB, `"${R_HOME}/bin/R" CMD config RANLIB`)

## seems unreliable as to whether this information is available
AR=`"${R_HOME}/bin/R" CMD config AR`
AS_IF([test "x$AR" = "xERROR: no information for variable 'AR'"], [AC_PATH_PROG([AR], [ar])], [])
AC_SUBST(AR)

# determine the location of the Rhdf5lib versions of the HDF5 library
RHDF5_INCLUDE=`echo 'cat(system.file("include", package="Rhdf5lib"))'|\
    "${R_HOME}/bin/R" --vanilla --slave`
AC_SUBST(RHDF5_INCLUDE)


echo "configuring the BLOSC filter...";
AX_GCC_X86_CPU_SUPPORTS(sse2, [SSE2="-DSHUFFLE_SSE2_ENABLED"], [SSE2=""])
AX_GCC_X86_CPU_SUPPORTS(avx2, [AVX2="-DSHUFFLE_AVX2_ENABLED"; MAVX2="-mavx2"], [AVX2=""; MAVX2=""])
AC_SUBST(SSE2)
AC_SUBST(AVX2)
AC_SUBST(MAVX2)
AC_CONFIG_FILES([src/blosc/lib/blosc-1.16.3/Makefile])
AC_OUTPUT

#update variables in Makevars
HDF5_INCLUDE="${BASEPBNAME}/src"
AC_SUBST(HDF5_INCLUDE)
AC_MSG_NOTICE([   HDF5_INCLUDE=${HDF5_INCLUDE}])

BZIP2_LIB="bzip2/libH5Zbz2.so"
BLOSC_LIB="blosc/libH5Zblosc.so"

AC_SUBST(BZIP2_LIB)
AC_SUBST(BLOSC_LIB)
AC_MSG_NOTICE([   BZIP2_LIB=${BZIP2_LIB}])
AC_MSG_NOTICE([   BLOSC_LIB=${BLOSC_LIB}])
AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
