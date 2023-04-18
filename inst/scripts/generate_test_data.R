## this function produces the file h5ex_filters.h5 found in inst/h5examples
## It is used to test reading functionality in the unit tests.

library(rhdf5)

filters <- c(
  "BLOSC",
  "BZIP",
  "LZF",
  "VBZ",
  "ZSTD"
)

h5file <- file.path(tempdir(), "h5ex_filters.h5")
if(file.exists(h5file)) file.remove(h5file)
dat <- c(rep(0, 100), 1:100)
fid <- H5Fcreate(h5file)
sid <- H5Screate_simple(dims = length(dat))
tid <- H5Tcopy("H5T_STD_U32LE")

for(filter in filters) {
  dcpl <- H5Pcreate("H5P_DATASET_CREATE")
  H5Pset_chunk(dcpl, dim = 50)
  switch(filter,
         "BLOSC" = rhdf5::H5Pset_blosc(dcpl, tid),
         "BZIP"  = rhdf5::H5Pset_bzip2(dcpl),
         "LZF"   = rhdf5::H5Pset_lzf(dcpl, tid),
         "VBZ"   = rhdf5::H5Pset_filter(dcpl, as.integer(32020), TRUE, c(1L, 2L, 1L, 1L)),
         "ZSTD"  = rhdf5::H5Pset_filter(dcpl, as.integer(32015), TRUE, c(1L))
  )
  did <- H5Dcreate(h5loc = fid, name = filter, dcpl = dcpl, 
                   h5space = sid, dtype_id = tid)
  H5Dwrite(did, dat)
  
  H5Pclose(dcpl)
  H5Dclose(did)
}

H5Sclose(sid)
H5Fclose(fid)
