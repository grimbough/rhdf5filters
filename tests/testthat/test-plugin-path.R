
test_that("HDF5_PLUGIN_PATH environment variable is set", {
    expect_true( nchar(Sys.getenv("HDF5_PLUGIN_PATH")) > 0 )
})

test_that("plugin path is returned", {
    expect_is(tmp <- hdf5_plugin_path(), "character")
    expect_true( grepl(pattern = "rhdf5filters/lib", x = tmp) )
})
