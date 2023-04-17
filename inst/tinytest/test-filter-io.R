
## write a matrix to a predefined dataset for testing
writeTestDataset <- function(file, data, filter, compression_level, shuffle) {
    
    rhdf5::h5createFile(file = file)
    rhdf5::h5createDataset(file, dataset = "test", dims = dim(data), 
                           filter = filter, storage.mode = "integer",
                           level = compression_level, shuffle = shuffle)
    rhdf5::h5write(obj = data, file = file, name = "test")
}

## we generate ints from the exponential distribution.  This has many 0's
## and generally compresses well with/and without shuffling.  Sampling from
## uniform distribution sometimes doesn't compress with shuffling turned off
mat <- matrix(as.integer(rexp(10000, rate = 1.5)), ncol = 10)
tf <- tempfile()
settings <- list("BLOSC_BLOSCLZ" = 0:1,
                 "BLOSC_LZ4"     = 0:9,
                 "BLOSC_LZ4HC"   = 0:9,
                 "BLOSC_SNAPPY"  = 0:1,
                 "BLOSC_ZLIB"    = 0:9,
                 "BLOSC_ZSTD"    = 0:9)

## this is the uncompressed file size for comparison in tests
writeTestDataset(file = tf, data = mat, filter = "BLOSC_BLOSCLZ", 
                 compression_level = 0, shuffle = FALSE)
max_file_size <- file.size(tf)
file.remove(tf)


    for(i in seq_along(settings)) {
        for(j in seq_along(settings[[i]])) {
            for(k in c(TRUE, FALSE)) {
                expect_silent(
                    writeTestDataset(file = tf, data = mat, filter = names(settings)[i], 
                                               compression_level = settings[[i]][j], shuffle = k)
                )
                if(settings[[i]][j] > 0) 
                    expect_true(file.size(tf) < max_file_size)
                expect_identical(
                    rhdf5::h5read(tf, "test"), mat
                )
                file.remove(tf)
            }
        }
    }


    for(j in seq_len(9)) {
        for(k in c(TRUE, FALSE)) {
            expect_silent(
                writeTestDataset(file = tf, data = mat, filter = "BZIP2", 
                                 compression_level = j, shuffle = k)
            )
            expect_true(file.size(tf) < max_file_size)
            expect_identical(
                rhdf5::h5read(tf, "test"), mat
            )
            file.remove(tf)
        }
    }
    
    for(k in c(TRUE, FALSE)) {
        expect_silent(
            writeTestDataset(file = tf, data = mat, filter = "LZF", 
                             compression_level = 1, shuffle = k)
        )
        expect_true(file.size(tf) < max_file_size)
        expect_identical(
            rhdf5::h5read(tf, "test"), mat
        )
        file.remove(tf)
    }

