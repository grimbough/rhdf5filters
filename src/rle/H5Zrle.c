#include <H5PLextern.h>

#include "rle.h"

static size_t H5Z_filter_rle(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_RLE 30007

const H5Z_class2_t H5Z_RLE[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_RLE,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 Run Length Encoding Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_rle, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_RLE;}


static size_t H5Z_filter_rle(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{

  size_t j, outbuflen, outdatalen;
  int ret;
  unsigned int bit32 = cd_values[0];
  uint8_t *outbuf;

  if (flags & H5Z_FLAG_REVERSE) {
    /** Decompressing the data **/

    size_t *orig_size_ptr = (size_t *)(*&buf[0]);
    outbuflen = orig_size_ptr[0];
    //fprintf(stdout, "outbuffer size: %lu\n", outbuflen);
      
    outbuf = (uint8_t *)malloc( outbuflen * sizeof( uint8_t ) );
    if (!outbuf) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }
    
    if(bit32) {
        rle_decompress_32bit(*buf, nbytes, outbuf);
    } else {
        rle_decompress_8bit(*buf, nbytes, outbuf);
    }

    outdatalen = outbuflen;


  } else {
    /** Compressing the data **/
    
    // allocate a buffer to write the encoded version to
    outbuf = (uint8_t *)calloc(nbytes + sizeof(size_t), sizeof(uint8_t));
    if (!outbuf) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }
    
    if(bit32) {
        outbuflen = rle_compress_32bit(*buf, nbytes, outbuf);
    } else {
        outbuflen = rle_compress_8bit(*buf, nbytes, outbuf);
    }
    
    //fprintf(stdout, "initial size: %lu, final size: %lu\n", nbytes + sizeof(size_t), outbuflen);
    
    /*for(int i=0; i < sizeof(size_t); i++){
        printf("%u ", outbuf[i]);
    }
    printf("\n");*/

    outdatalen = outbuflen;

  }

  /* Always replace the input buffer with the output buffer. */
  free(*buf);
  *buf = outbuf;
  *buf_size = outbuflen;
  return outdatalen;

  cleanupAndFail:
  if (outbuf)
    free(outbuf);
  return 0;
}