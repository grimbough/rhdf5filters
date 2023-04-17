library(rhdf5filters)

expect_true( nchar(Sys.getenv("HDF5_PLUGIN_PATH")) > 0 )

expect_inherits(tmp <- hdf5_plugin_path(), "character")
expect_true( grepl(pattern = "rhdf5filters/lib", x = tmp) )

