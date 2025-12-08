test_that("plugin path", {
  expect_true(nchar(Sys.getenv("HDF5_PLUGIN_PATH")) == 0)

  expect_type(tmp <- hdf5_plugin_path(), "character")
  expect_true(grepl(pattern = "rhdf5filters/lib", x = tmp))
})

