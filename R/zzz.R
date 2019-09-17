

.onLoad <- function(libname, pkgname) {
    
    path <- Sys.getenv(
        x = "HDF5FILTERS_RPATH",
        unset = system.file("lib", package="hdf5Filters", mustWork=TRUE)
    )
    
    if (nzchar(.Platform$r_arch)) {
        arch <- sprintf("/%s", .Platform$r_arch)
    } else {
        arch <- ""
    }
    patharch <- paste0(path, arch)
    
    Sys.setenv(HDF5_PLUGIN_PATH=patharch)
}

#' @export
pkgconfig <- function(opt = c("PKG_LIB")) {
    
    path <- Sys.getenv(
        x = "HDF5FILTERS_RPATH",
        unset = system.file("lib", package="hdf5Filters", mustWork=TRUE)
    )
    
    if (nzchar(.Platform$r_arch)) {
        arch <- sprintf("/%s", .Platform$r_arch)
    } else {
        arch <- ""
    }
    patharch <- paste0(path, arch)
    
    result <- switch(match.arg(opt), 
                     PKG_LIB = {
                         switch(Sys.info()['sysname'], 
                                Linux = {
                                    sprintf('-Wl,-rpath=%s -L%s -lH5Zlz4 -lh5blosc',
                                            patharch, patharch)
                                #}, Darwin = {
                                #     sprintf('%s/libhdf5.a %s/libsz.a', 
                                #             patharch, patharch)
                                # }, Windows = {
                                #     patharch <- gsub(x = shortPathName(patharch),
                                #                      pattern = "\\",
                                #                      replacement = "/", 
                                #                      fixed = TRUE)
                                #     sprintf('-L%s -lhdf5 -lszip -lz -lpsapi', 
                                #             patharch)
                                }
                         )
                     } 
    )
    
    cat(result)
}