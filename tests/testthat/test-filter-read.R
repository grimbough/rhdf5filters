original_data <- array(c(rep(0, 100), 1:100))
example_file <- system.file("h5examples", "h5ex_filters.h5", package = "rhdf5filters")

test_that("BZIP read example", {
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = "BZIP"),
    original_data
  )
})

test_that("LZF read example", {
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = "LZF"),
    original_data
  )
})

test_that("BLOSC read example (when available)", {
  skip_if_not("blosc" %in% available_filters(), "BLOSC filter not available")
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = "BLOSC"),
    original_data
  )
})

test_that("VBZ read example (when available)", {
  skip_if_not("vbz" %in% available_filters(), "VBZ filter not available")
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = "VBZ"),
    original_data
  )
})

test_that("ZSTD read example (when available)", {
  skip_if_not("zstd" %in% available_filters(), "ZSTD filter not available")
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = "ZSTD"),
    original_data
  )
})

