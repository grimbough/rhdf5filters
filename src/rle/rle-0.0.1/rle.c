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
    while( i < buffer_size &&
            buffer_ptr[i] == output_buffer[j-1] &&
           k < MAX_REPEATS &&
           k < buffer_size ) {
      k++;
      i++;
    }
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


size_t rle_compress_32bit(void *buffer, size_t buffer_size, uint8_t *output_buffer) {
    
    size_t i = 0;
    size_t j = sizeof(size_t); 
    size_t output_size;
    uint8_t k;
    uint32_t *buffer_ptr = (uint32_t *) buffer;
    uint32_t previous_val, current_val = 0;
    
    // write the size of the original buffer in the first bytes
    size_t *size_ptr = (size_t*)(&output_buffer[0]);
    *size_ptr = buffer_size;
    
    while(i < (buffer_size / sizeof(uint32_t))) {
        k = 0;
        
        current_val = buffer_ptr[i];

        while(buffer_ptr[i] == current_val &&
              k < MAX_REPEATS && 
              k < (buffer_size/sizeof(uint32_t)) ) {
            k++;
            i++;
        }
        
        //printf("k: %u val: %u\n", k, current_val);
        
        output_buffer[j++] = k;
        output_buffer[j++] = (unsigned int)(current_val & 0xff);
        output_buffer[j++] = (unsigned int)(current_val >> 8) & 0xff;
        output_buffer[j++] = (unsigned int)(current_val >> 16) & 0xff;
        output_buffer[j++] = (unsigned int)(current_val >> 24);
    }
    
    output_size = j;
    //printf("output_size: %lu\n", output_size);
    
    /*
    j = sizeof(size_t);
    while(j < output_size) {
        printf("%u %u %u %u %u\n", output_buffer[j], output_buffer[j+1], output_buffer[j+2], output_buffer[j+3], output_buffer[j+4]);
        j += 5;
    } */
    
    
    return(output_size);
}

void rle_decompress_32bit(uint8_t *buffer, size_t buffer_size, uint8_t *output_buffer ) {
    
    uint8_t k, count;
    size_t i = sizeof(size_t);
    size_t j = 0;
    uint8_t val[4];
    
    while(i < buffer_size) {
        count = buffer[i++];
        
        val[0] = buffer[i++];
        val[1] = buffer[i++];
        val[2] = buffer[i++];
        val[3] = buffer[i++];
        
        for( k = 0; k < count; k++ ) {
            output_buffer[j++] = val[0];
            output_buffer[j++] = val[1];
            output_buffer[j++] = val[2];
            output_buffer[j++] = val[3];
        }
    }
    
}

