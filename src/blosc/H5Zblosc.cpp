 /*
 * This file is an example of an HDF5 filter plugin. 
 * The filter function  H5Z_filter_blosc was adopted from 
 * PyTables http://www.pytables.org.  
 * The plugin can be used with the HDF5 library vesrion 1.8.11 to read
 * HDF5 datasets compressed with blosc created by PyTables. 
 */

/*
 *
Copyright Notice and Statement for PyTables Software Library and Utilities:

Copyright (c) 2002-2004 by Francesc Alted
Copyright (c) 2005-2007 by Carabos Coop. V.
Copyright (c) 2008-2010 by Francesc Alted
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

a. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

b. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.

c. Neither the name of Francesc Alted nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <H5PLextern.h>

#include <blosc.h>

static size_t H5Z_filter_blosc(unsigned flags, size_t cd_nelmts,
                    const unsigned cd_values[], size_t nbytes,
                    size_t *buf_size, void **buf);

/* Filter revision number, starting at 1 */
/* #define FILTER_BLOSC_VERSION 1 */
#define H5Z_FILTER_BLOSC_VERSION 2  /* multiple compressors since Blosc 1.3 */
/* Filter ID registered with the HDF Group */
#define H5Z_FILTER_BLOSC 32001


const H5Z_class2_t H5Z_BLOSC[1] = {{
    H5Z_CLASS_T_VERS,       /* H5Z_class_t version */
    (H5Z_filter_t)H5Z_FILTER_BLOSC,         /* Filter id number */
    1,              /* encoder_present flag (set to true) */
    1,              /* decoder_present flag (set to true) */
    "HDF5 blosc filter",
                                /* Filter name for debugging */
    NULL,                       /* The "can apply" callback */
    NULL,                       /* The "set local" callback */
    (H5Z_func_t)H5Z_filter_blosc,         /* The actual filter function */
}};

H5PL_type_t   H5PLget_plugin_type(void) {return H5PL_TYPE_FILTER;}
const void *H5PLget_plugin_info(void) {return H5Z_BLOSC;}

/* The filter function */
static size_t H5Z_filter_blosc(unsigned flags, size_t cd_nelmts,
                    const unsigned cd_values[], size_t nbytes,
                    size_t *buf_size, void **buf){

    void* outbuf = NULL;
    int status = 0;                /* Return code from Blosc routines */
    size_t typesize;
    size_t outbuf_size;
    int clevel = 5;                /* Compression level default */
    int doshuffle = 1;             /* Shuffle default */
    int compcode = 0;              /* Blosc compressor */
    int code;
    const char *compname = NULL;
    const char *complist;
    
    //int nthreads = 4;
    //int pnthreads = blosc_set_nthreads(nthreads);
    //printf("Using %d threads (previously using %d)\n", nthreads, pnthreads);

    /* Filter params that are always set */
    typesize = cd_values[2];      /* The datatype size */
    outbuf_size = cd_values[3];   /* Precomputed buffer guess */
    /* Optional params */
    if (cd_nelmts >= 5) {
        clevel = cd_values[4];        /* The compression level */
    }
    if (cd_nelmts >= 6) {
        doshuffle = cd_values[5];     /* Shuffle? */
    }
    if (cd_nelmts >= 7) {
        compcode = cd_values[6];     /* The Blosc compressor used */
	/* Check that we actually have support for the compressor code */
        complist = blosc_list_compressors();
    	code = blosc_compcode_to_compname(compcode, &compname);
    	if (code == -1) {
    	    fprintf(stderr, "blosc filter: this Blosc library does not have support for "
                 "the '%s' compressor, but only for: %s\n",
    		    compname, complist);
                goto failed;
    	}
    }   

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
            fprintf(stderr, "blosc_filter: Can't allocate compression buffer\n");
            goto failed;
        }

	/* Select the correct compressor to use */
        if (compname != NULL)
	  blosc_set_compressor(compname);

        status = blosc_compress(clevel, doshuffle, typesize, nbytes,
                                *buf, outbuf, nbytes);
        if (status < 0) {
          fprintf(stderr, "blosc_filter: Blosc compression error\n");
          goto failed;
        }

    /* We're decompressing */
    } else {
        /* declare dummy variables */
        size_t cbytes, blocksize;

        free(outbuf);

        /* Extract the exact outbuf_size from the buffer header.
         *
         * NOTE: the guess value got from "cd_values" corresponds to the
         * uncompressed chunk size but it should not be used in a general
         * cases since other filters in the pipeline can modify the buffere
         *  size.
         */
        blosc_cbuffer_sizes(*buf, &outbuf_size, &cbytes, &blocksize);

        outbuf = malloc(outbuf_size);

        if(outbuf == NULL){
          fprintf(stderr, "blosc_filter: Can't allocate decompression buffer\n");
          goto failed;
        }

        status = blosc_decompress(*buf, outbuf, outbuf_size);

        if(status <= 0){    /* decompression failed */
          fprintf(stderr,"blosc_filter: Blosc decompression error\n");
          goto failed;
        } /* if !status */

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
