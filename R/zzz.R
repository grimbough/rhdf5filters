
.onLoad <- function(libname, pkgname) {
    
    patharch <- hdf5_plugin_path()
    existing_path <- Sys.getenv("HDF5_PLUGIN_PATH")
    
    ## retain any existing plugin locations
    if(nzchar(existing_path)) {
      sep = if(.Platform$OS.type == "windows") ";" else ":"
      patharch <- paste(patharch, existing_path, sep = sep)
    }
    
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

#' Return a list of installed filters
#' 
#' This function can be used to produce a vector of the installed filters.
#' 
#' @return A character vector containing the names of the installed filters.
#' @examples
#' available_filters()
#' 
#' @export
available_filters <- function() {
  
  path <- system.file("lib", package="rhdf5filters", mustWork=FALSE)
  object_files <- tools::file_path_sans_ext(list.files(path))
  filters <- sub(pattern = "libH5Z", replacement = "", x = object_files)
  return(filters)
}