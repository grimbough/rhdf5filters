#include "rle.h"

#define MAX_REPEATS 255

size_t rle_compress_8bit(void *buffer, size_t buffer_size, uint8_t *output_buffer) {

  size_t i = 0;
  size_t j = sizeof(size_t); 
  size_t output_size;
  uint8_t k;
  uint8_t *buffer_ptr = (uint8_t *) buffer;

  // write the size of the original buffer in the first bytes
  size_t *size_ptr = (size_t*)(&output_buffer[0]);
  *size_ptr = buffer_size;

  while(i < buffer_size) {
    k = 0;
    // record current value
    output_buffer[j++] = buffer_ptr[i];
    while( buffer_ptr[i] == output_buffer[j-1] &&
           k < MAX_REPEATS &&
           k < buffer_size ) {
      k++;
      i++;
    }
    //printf("j: %lu k: %u\n", j, k);
    output_buffer[j++] = k;
  }

  output_size = j;
  return(output_size);
}


void rle_decompress_8bit(uint8_t *buffer, size_t buffer_size, uint8_t *output_buffer ) {

  uint8_t val, k, count;
  size_t i = sizeof(size_t);
  size_t j = 0;

  while(i < buffer_size) {
      val = buffer[i++];
      count = buffer[i++];
      for( k = 0; k < count; k++ ) {
          output_buffer[j++] = val;
      }
  }

}

