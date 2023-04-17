
original_data <- array(c(rep(0, 100), 1:100))
example_file <- system.file("h5examples", "h5ex_filters.h5", package = "rhdf5filters")

filters <- c(
  "BLOSC",
  "BZIP",
  "LZF",
  "VBZ"
)

for(filter in filters) {
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = filter),
    original_data
  )
}
