#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

size_t rle_compress_8bit(void *buffer, size_t buffer_size, uint8_t *output_buffer);
void rle_decompress_8bit(uint8_t *buffer, size_t buffer_size, uint8_t *output_buffer);

size_t rle_compress_32bit(void *buffer, size_t buffer_size, uint8_t *output_buffer);
void rle_decompress_32bit(uint8_t *buffer, size_t buffer_size, uint8_t *output_buffer);
