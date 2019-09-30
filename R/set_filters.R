
#' LZF Filter
H5Pset_lzf <- function( h5plist ) {
    
    if(!is.loaded('_H5Pset_lzf', PACKAGE = 'rhdf5'))
        stop('LZF filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_lzf", h5plist@ID, PACKAGE='rhdf5')
    invisible(res)
}

## LZ4 Filter
H5Pset_lz4 <- function( h5plist ) {
    
    if(!is.loaded('_H5Pset_lz4', PACKAGE = 'rhdf5'))
        stop('LZ4 filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_lz4", h5plist@ID, PACKAGE='rhdf5')
    invisible(res)
}

## BZIP2 Filter
#' @export
H5Pset_bzip2 <- function( h5plist, level = 2L ) {
    
    if(!is.loaded('_H5Pset_bzip2', PACKAGE = 'rhdf5'))
        stop('LZ4 filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_bzip2", h5plist@ID, as.integer(level), PACKAGE='rhdf5')
    invisible(res)
}

## BLOSC Filter
## Filter from https://github.com/nexusformat/HDF5-External-Filter-Plugins/
## contains a call to blosc_set_local() which determines chunk size & blosc
## parameters. This requires calls to HDF5 functions and doesn't play well
## with our static linking.  We move this setup code into the function below.
#' @export
H5Pset_blosc <- function( h5plist, h5tid, method = 1L, level = 6L ) {
    
    if(!is.loaded('_H5Pset_blosc', PACKAGE = 'rhdf5'))
        stop('BLOSC filter not found.  Please reinstall rhdf5.')
    
    if(!method %in% 1:6) {
        method <- 1L
        warning('Invalid method selected.  Using blosclz')
    }

    ## simplified reimplementation of C code from H5Zblosc.c
    chunkdims <- H5Pget_chunk(h5plist)

    typesize <- rhdf5:::H5Tget_size(h5tid)
    if(typesize > 255) { typesize <- 1 }

    bufsize <- typesize * prod(chunkdims)
    ## END
    

    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_blosc", h5plist@ID, 
        as.integer(method-1L), as.integer(level), 
        as.integer(typesize), as.integer(bufsize),
        PACKAGE='rhdf5')
    invisible(res)
}