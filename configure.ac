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
    
#echo "building BZIP2 filter..."
#cd src/bzip2/bzip2-1.0.8;
#$MAKE
#cd ../
#${CC} ${CFLAGS} ${CPICFLAGS} -shared H5Zbzip2.c -I$RHDF5_INCLUDE -I./bzip2-1.0.8/ ./bzip2-1.0.8/libbz2.a -o #libH5Zbz2.so
#cd ../../

#echo "building the BLOSC filter...";
#cd src/blosc/
#$MAKE CC="${CC}" CFLAGS="${CFLAGS}" CPICFLAGS="${CPICFLAGS}" CXX="${CXX}" CXXFLAGS="${CXXFLAGS}" CXXPICFLAGS#="${CXXPICFLAGS}" CPPFLAGS="-I${RHDF5_INCLUDE}" AR="${AR}" MAKE="${MAKE}"
#cd ../../


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
