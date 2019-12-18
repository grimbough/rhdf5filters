#' Set HDF5 compression filters
#' 
#' Set compressions filters when working with dataset creation property lists.
#' 
#' These functions can be used to set the compression filter when working
#' with dataset creation property lists directly.
#'
#' @param h5plist HDF5 dataset creation property list
#' @param h5tid HDF5 type ID
#' @param level Compression level to use
#' @param method When using the BLOSC filter, defines which compression tool 
#' should be used.
#' @param shuffle Logical value determining whether byte shuffling should be
#' applied before compression is applied. This only applies to the BLOSC 
#' filter (see details below).
#' 
#' @name filters
NULL

## BZIP2 Filter
#' @rdname filters
#' @export
H5Pset_bzip2 <- function( h5plist, level = 2L ) {
    
    if(!is.loaded('_H5Pset_bzip2', PACKAGE = 'rhdf5'))
        stop('LZ4 filter not found.  Please reinstall rhdf5.')
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_bzip2", h5plist@ID, as.integer(level), PACKAGE='rhdf5')
    invisible(res)
}

## BLOSC Filter
#' @rdname filters
#' @export
H5Pset_blosc <- function( h5plist, h5tid, method = 1L, level = 6L, shuffle = TRUE ) {
    
    if(!is.loaded('_H5Pset_blosc', PACKAGE = 'rhdf5'))
        stop('BLOSC filter not found.  Please reinstall rhdf5.')
    
    if(!method %in% 1:6) {
        method <- 1L
        warning('Invalid method selected.  Using BLOSC_LZ')
    }

    ## START: simplified reimplementation of C code from H5Zblosc.c
    ## Filter from https://github.com/nexusformat/HDF5-External-Filter-Plugins/
    ## contains a call to blosc_set_local() which determines chunk size & blosc
    ## parameters. This requires calls to HDF5 functions and doesn't play well
    ## with our static linking.  We move this setup code into R code below.
    chunkdims <- H5Pget_chunk(h5plist)
    typesize <- rhdf5:::H5Tget_size(h5tid)
    if(typesize > 255) { typesize <- 1 }
    bufsize <- typesize * prod(chunkdims)
    ## END
    
    rhdf5:::h5checktypeAndPLC(h5plist, "H5P_DATASET_CREATE")
    res <- .Call("_H5Pset_blosc", h5plist@ID, 
        as.integer(method-1L), as.integer(level), 
        as.integer(as.logical(shuffle)),
        as.integer(typesize), as.integer(bufsize),
        PACKAGE='rhdf5')
    invisible(res)
}