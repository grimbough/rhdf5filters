
.onLoad <- function(libname, pkgname) {
    
    patharch <- hdf5_plugin_path()
    Sys.setenv(HDF5_PLUGIN_PATH=patharch)
}

#' Return location of installed filters
#' 
#' This function can be used to find the location of the installed filters.
#' Setting the environment variable HDF5_PLUGIN_PATH to this value will allow
#' other applications that require the the filters to use the versions
#' distributed with this package.
#' 
#' @return A character string containing the path where the compiled filters
#' are located.
#' @examples
#' hdf5_plugin_path()
#' 
#' @export
hdf5_plugin_path <- function() {
    
    path <- system.file("lib", package="rhdf5filters", mustWork=FALSE)
    
    ## record the architecture if it exists
    if (nzchar(.Platform$r_arch)) {
        arch <- sprintf("/%s", .Platform$r_arch)
    } else {
        arch <- ""
    }
    patharch <- paste0(path, arch)
    
    return(patharch)
}