
original_data <- array(c(rep(0, 100), 1:100))
example_file <- system.file("h5examples", "h5ex_filters.h5", package = "rhdf5filters")

filters <- c(
  "BZIP",
  "LZF"
)

if("blosc" %in% available_filters())
  filters <- c(filters, "BLOSC")
if("vbz" %in% available_filters())
  filters <- c(filters, "VBZ")
if("zstd" %in% available_filters())
  filters <- c(filters, "ZSTD")


for(filter in filters) {
  expect_equivalent(
    rhdf5::h5read(file = example_file, name = filter),
    original_data
  )
}
