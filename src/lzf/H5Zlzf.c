/* Additional preamble *****************************************************
* 
* This is a modified version of the original source found in h5py
* Copyright (C) 2021 Mike L Smith
* License: BSD  (See /src/LICENSES/LZF.txt for full license)
*
******************************************************************************/


/***** Preamble block *********************************************************
*
* This file is part of h5py, a low-level Python interface to the HDF5 library.
*
* Copyright (C) 2008 Andrew Collette
* http://h5py.org
* License: BSD  (See LICENSE.txt for full license)
*
* $Date$
*
****** End preamble block ****************************************************/

/*
    Implements an LZF filter module for HDF5, using the BSD-licensed library
    by Marc Alexander Lehmann (http://www.goof.com/pcg/marc/liblzf.html).

    No Python-specific code is used.  The filter behaves like the DEFLATE
    filter, in that it is called for every type and space, and returns 0
    if the data cannot be compressed.

    The only public function is (int) register_lzf(void), which passes on
    the result from H5Zregister.
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <H5PLextern.h>
#include "hdf5.h"

#include "lzf.h"

#define H5Z_FILTER_LZF_VERSION 4
#define H5Z_FILTER_LZF 32000

size_t H5Z_filter_lzf(unsigned int flags, size_t cd_nelmts,
		              const unsigned cd_values[], size_t nbytes,
		              size_t *buf_size, void **buf);

const H5Z_class2_t H5Z_LZF[1] = {{
    H5Z_CLASS_T_VERS,
    (H5Z_filter_t)(H5Z_FILTER_LZF),
    1, 
    1,
    "HDF5 lzf filter",
    NULL,
    NULL,
    (H5Z_func_t)(H5Z_filter_lzf),
}};

H5PL_type_t H5PLget_plugin_type(void) { return H5PL_TYPE_FILTER; }
const void *H5PLget_plugin_info(void) { return H5Z_LZF; }

/* The filter function */
size_t H5Z_filter_lzf(unsigned int flags, size_t cd_nelmts,
		              const unsigned cd_values[], size_t nbytes,
		              size_t *buf_size, void **buf) {

    void* outbuf = NULL;
    size_t outbuf_size = 0;

    unsigned int status = 0;        /* Return code from lzf routines */

    /* We're compressing */
    if(!(flags & H5Z_FLAG_REVERSE)){

        /* Allocate an output buffer exactly as long as the input data; if
           the result is larger, we simply return 0.  The filter is flagged
           as optional, so HDF5 marks the chunk as uncompressed and
           proceeds.
        */

        outbuf_size = (*buf_size);
        outbuf = malloc(outbuf_size);

        if(outbuf == NULL){
            goto failed;
        }

        status = lzf_compress(*buf, nbytes, outbuf, outbuf_size);

    /* We're decompressing */
    } else {

        if((cd_nelmts>=3)&&(cd_values[2]!=0)){
            outbuf_size = cd_values[2];   /* Precomputed buffer guess */
        }else{
            outbuf_size = (*buf_size);
        }

#ifdef H5PY_LZF_DEBUG
        fprintf(stderr, "Decompress %d chunk w/buffer %d\n", nbytes, outbuf_size);
#endif

        while(!status){

            free(outbuf);
            outbuf = malloc(outbuf_size);

            if(outbuf == NULL){
                goto failed;
            }

            status = lzf_decompress(*buf, nbytes, outbuf, outbuf_size);

            if(!status){    /* compression failed */

                if(errno == E2BIG){
                    outbuf_size += (*buf_size);
#ifdef H5PY_LZF_DEBUG
                    fprintf(stderr, "    Too small: %d\n", outbuf_size);
#endif
                } else if(errno == EINVAL) {
                    goto failed;

                } else {
                    goto failed;
                }

            } /* if !status */

        } /* while !status */

    } /* compressing vs decompressing */

    if(status != 0){

        free(*buf);
        *buf = outbuf;
        *buf_size = outbuf_size;

        return status;  /* Size of compressed/decompressed data */
    }

    failed:

    free(outbuf);
    return 0;

} /* End filter function */
