#include <H5PLextern.h>
#include "simdcomp.h"

static size_t H5Z_filter_sdc(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_SIMDCOMP 30010

const H5Z_class2_t H5Z_SDC[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_SIMDCOMP,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 simdcomp Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_sdc, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_SDC;}


static size_t H5Z_filter_sdc(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{

  size_t outdatasize;
  int ret;
  int calc_bit = 0;
  unsigned int bit = cd_values[0];
  int offset = sizeof(size_t);
  int length;
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

    uint32_t *backdata = (uint32_t *)malloc(outdatasize * sizeof(uint32_t));
    if (backdata == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    inbuf = (char *)(*&buf[0]);
    simdunpack_length((const __m128i *)data_ptr, length, backdata, bit);

    outbuf = (char *)&backdata[0];

  } else {

    /** Compressing the data **/

    /* we expect 32-bit ints, so cast buf to that */
    uint32_t *input = (uint32_t *)(*&buf[0]);

    length = nbytes / sizeof(uint32_t);

    if(bit == 0) {
      calc_bit = 1;
      bit = maxbits_length(input, length);
    }

    //fprintf(stdout, "bit: %u\n", bit);

    outdatasize = simdpack_compressedbytes(length, bit);

    // allocate a buffer to write the encoded version to
    uint8_t  *buffer = malloc((sizeof(uint8_t) * outdatasize) + offset + calc_bit);
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

    __m128i * endofbuf = simdpack_length(input, length, (__m128i *)data_ptr, bit);
    int howmanybytes = (endofbuf-(__m128i *)data_ptr)*sizeof(__m128i);

    outbuf = (char *)&buffer[0];

    /*
    for(int i = 0; i<outdatasize;i++) { printf("%hhu ", outbuf[i]); }
      printf("\n");
    */
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