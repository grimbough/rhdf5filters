# rhdf5filters 1.14.0

## CHANGES

* The package will now test for system libraries for several compression tools
and will use those libraries rather than compiling from source if they are
found.

# rhdf5filters 1.12.0

## USER VISIBLE CHANGES

* Compression libraries updated:
  - lz4: 1.9.2 🠪 1.9.4
* Added the standalone Zstandard filter.  The distributed version of Zstandard
is now 1.5.5.
* Added the VBZ filter.
  
## BUG FIXES

* Ensure ranlib is applied to the lzf library after it is compiled.  This 
cause linking failures on some systems.  (Thanks to 
Sergey Fedorov for the report https://github.com/grimbough/rhdf5filters/pull/18)

# rhdf5filters 1.4.0

## USER VISIBLE CHANGES

* Compression libraries updated:
  - blosc: 1.16.3 🠪 1.20.1 
  - lz4: 1.8.3 🠪 1.9.2
  - zstd: 1.3.8 🠪 1.4.5
  
* Added LZF filter
  
## BUG FIXES

* Fixed some missing references to `CFLAGS`, `CPPFLAGS` & `LDFLAGS` in 
  package compilation (https://github.com/grimbough/rhdf5filters/pull/4)
* Improved CPU detection on non-x86 architecture to allow compilation to
  proceed with default instruction sets, rather than failing to install.
  (https://github.com/grimbough/rhdf5filters/issues/3)
* Address issue in compilation where message printed while processing
  .Rprofile where added to `LDFLAGS`
  (https://github.com/grimbough/rhdf5filters/issues/11) (#11)

# rhdf5filters 1.2.0

## BUG FIXES

* Now passes `R CMD config LDFLAGS` to the compilation of the BLOSC filter.
  (https://github.com/grimbough/rhdf5filters/issues/2)

# rhdf5filters 0.99.0

* Initial submission to Bioconductor
