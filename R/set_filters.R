
## LZF Filter
H5Pset_lzf <- function( h5plist ) {
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_lzf", h5plist@ID, PACKAGE='hdf5Filters')
    invisible(res)
}

## LZ4 Filter
#H5Pset_lz4 <- function( h5plist ) {
#    h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
#    res <- .Call("_H5Pset_lz4", h5plist@ID, PACKAGE='hdf5Filters')
#    invisible(res)
#}
