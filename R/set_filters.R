
#' LZF Filter
#' @export
H5Pset_lzf <- function( h5plist ) {
    
    if(!is.loaded('_H5Pset_lzf', PACKAGE = 'rhdf5'))
        stop('LZF filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_lzf", h5plist@ID, PACKAGE='rhdf5')
    invisible(res)
}

## LZ4 Filter
#' @export
H5Pset_lz4 <- function( h5plist ) {
    
    if(!is.loaded('_H5Pset_lz4', PACKAGE = 'rhdf5'))
        stop('LZ4 filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_lz4", h5plist@ID, PACKAGE='rhdf5')
    invisible(res)
}

## BLOSC Filter
#' @export
H5Pset_blosc <- function( h5plist ) {
    
    if(!is.loaded('_H5Pset_blosc', PACKAGE = 'rhdf5'))
        stop('BLOSC filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_blosc", h5plist@ID, PACKAGE='rhdf5')
    invisible(res)
}