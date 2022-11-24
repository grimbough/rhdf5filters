#include <H5PLextern.h>
#include "Turbo-Run-Length-Encoding/trle.h"

static size_t H5Z_filter_turborle(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf);

#define H5Z_FILTER_TURBORLE 30011

const H5Z_class2_t H5Z_TURBORLE[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_TURBORLE,         /* Filter id number             */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 Turbo Run Length Encoding Filter",
                                /* Filter name for debugging    */
    NULL,                       /* The "can apply" callback     */
    NULL,                       /* The "set local" callback     */
    (H5Z_func_t)H5Z_filter_turborle, /* The actual filter function   */
}};

H5PL_type_t H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_TURBORLE;}


static size_t H5Z_filter_turborle(unsigned int flags, size_t cd_nelmts,
                     const unsigned int cd_values[], size_t nbytes,
                     size_t *buf_size, void **buf)
{
  unsigned char *outbuf = NULL;
  unsigned char *buf_ptr = (unsigned char *)(*&buf[0]);
  size_t outbuflen, outdatalen;
  int ret;

  if (flags & H5Z_FLAG_REVERSE) {

    /** Decompressing the data **/

    outbuf = (unsigned char *)malloc((10 * nbytes) + 1024);
    if (outbuf == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    outbuflen = trled(buf_ptr, *buf_size, outbuf, 10*nbytes);

    outdatalen = outbuflen;


  } else {

    /** Compressing the data **/

    outbuf = (unsigned char *)malloc(nbytes*4/3+1024);
    if (outbuf == NULL) {
      fprintf(stderr, "memory allocation failed for rle compression\n");
      goto cleanupAndFail;
    }

    outbuflen = trlec(buf_ptr, nbytes, outbuf);
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