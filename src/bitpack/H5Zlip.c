#include <H5PLextern.h>
#include "bitpacking.h"

//#define DEBUG 1

/* find the largest element in an array */
uint32_t largest(uint32_t arr[], size_t n)
{
    size_t i;
    uint32_t max = arr[0];
 
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
 
    return max;
}

/* compute the minimum number of bits required to represent a uint32 */
unsigned int mylog2 (uint32_t val) {
    if (val == 0 || val == 1) return 1;
    unsigned int ret = 0;
    while (val > 1) {
        val >>= 1;
        ret++;
    }
    return ret + 1;
}

static size_t H5Z_filter_lbp(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_LBP 30009

const H5Z_class2_t H5Z_LBP[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_LBP,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 LittleBitPacker Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_lbp, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_LBP;}


static size_t H5Z_filter_lbp(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{

  size_t outdatasize;
  int ret;
  unsigned int bit = cd_values[0];
  int offset = sizeof(size_t);
  int length;
  int calc_bit = 0;
  char *outbuf, *inbuf;

  if (flags & H5Z_FLAG_REVERSE) {

    /** Decompressing the data **/
    size_t *size_ptr = (size_t*)(*&buf[0]);
    uint8_t *data_ptr = (uint8_t*)(*&buf[0]);
    data_ptr += offset;

    /* if we're setting max bit on each chunk, store it */
    if(bit == 0) {
      bit = data_ptr[0];
      data_ptr++;
    }

    /* size is in bytes, length is number of array elements */
    outdatasize = size_ptr[0];
    length = outdatasize / sizeof(uint32_t);

    uint32_t *backdata = (uint32_t *)malloc(outdatasize * sizeof(uint32_t) + 64 * sizeof(uint32_t) );
    if (backdata == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    inbuf = (char *)(*&buf[0]);
    turbounpack32(data_ptr, length, bit, backdata);

    outbuf = (char *)&backdata[0];

  } else {

    /** Compressing the data **/

    /* we expect 32-bit ints, so cast buf to that */
    uint32_t *input = (uint32_t *)(*&buf[0]);

    length = nbytes / sizeof(uint32_t);

    if(bit == 0) {
      calc_bit = 1;
      bit = mylog2(largest(input, length));
    }

    outdatasize = byte_count(length, bit);
    
#ifdef DEBUG
    fprintf(stdout, "outdatasize: %lu, offset: %u, calc_bit: %u\n", outdatasize, offset, calc_bit);
#endif

    // allocate a buffer to write the encoded version to
    uint8_t  *buffer = malloc((2 * length + 1024) * sizeof(uint32_t) + 32 + offset + calc_bit);
    if (buffer == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    size_t *size_ptr = (size_t*)(&buffer[0]);
    uint8_t *data_ptr = (uint8_t*)(&buffer[offset]);

    *size_ptr = nbytes;
    if(calc_bit) {
      *data_ptr = bit;
      data_ptr++;
    }

    /* output size includes data, original size, (and stored max bit) */
    outdatasize += (offset + calc_bit);

    turbopack32(input, length, bit, data_ptr);

    outbuf = (char *)&buffer[0];
  }

  /* Always replace the input buffer with the output buffer. */
  free(*buf);
  *buf = outbuf;
  *buf_size = outdatasize;
  return outdatasize;

  cleanupAndFail:
  if (outbuf)
    free(outbuf);
  return 0;
}