

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