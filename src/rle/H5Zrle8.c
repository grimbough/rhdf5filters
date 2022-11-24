#include <H5PLextern.h>

#include "rle8.h"

static size_t H5Z_filter_rle8(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_RLE8 30008

const H5Z_class2_t H5Z_RLE8[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_RLE8,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 Run Length Encoding Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_rle8, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_RLE8;}


static size_t H5Z_filter_rle8(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{
  char *outbuf = NULL;
  size_t outbuflen, outdatalen;
  int ret;
  uint8_t j = sizeof(size_t);

  if (flags & H5Z_FLAG_REVERSE) {

    /** Decompressing the data **/

    size_t *size_ptr = (size_t *)(*&buf[0]);
    uint8_t *data_ptr = (uint8_t *)(*&buf[0]);
    data_ptr += j;

    outbuflen = size_ptr[0];

    // Allocate Output Buffer.
    uint8_t *pDecompressedData = (uint8_t *)malloc(outbuflen);

    if (pDecompressedData == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    const uint32_t decompressedSize = rle8_decompress(data_ptr, nbytes, pDecompressedData, outbuflen);

    outdatalen = outbuflen;

    free(*buf);
    *buf = pDecompressedData;
    *buf_size = outbuflen;


  } else {

    /** Compressing the data **/

    const uint32_t compressedBufferSize = rle8_compress_bounds(nbytes);
    uint8_t *pCompressedData = (uint8_t *)malloc(compressedBufferSize + j);
    if (pCompressedData == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    // write the size of the original buffer in the first bytes
    size_t *size_ptr = (size_t*)(&pCompressedData[0]);
    *size_ptr = nbytes; 

    const uint32_t compressedSize = rle8_compress(*buf, nbytes, &pCompressedData[j], compressedBufferSize);

    outbuflen = (size_t) compressedSize + j;
    outdatalen = outbuflen;

      /* Always replace the input buffer with the output buffer. */
    free(*buf);
    *buf = pCompressedData;
    *buf_size = outbuflen;

  }

  return outdatalen;

  cleanupAndFail:
  if (outbuf)
    free(outbuf);
  return 0;
}