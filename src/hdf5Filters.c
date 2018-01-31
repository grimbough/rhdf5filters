/* do not remove */

#include <R.h>
#include <Rdefines.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Error.h>
#include "hdf5.h"

// from lzf_filter.h
#define H5PY_FILTER_LZF_VERSION 4
#define H5PY_FILTER_LZF 32000
int register_lzf(void);

#define H5Z_FILTER_LZ4 32004


SEXP _H5Pset_deflate( SEXP _plist_id, SEXP _level ) {
    hid_t plist_id = INTEGER(_plist_id)[0];
    unsigned int level = (unsigned int)INTEGER(_level)[0];
    herr_t herr = H5Pset_deflate(plist_id, level);
    SEXP Rval = ScalarInteger(herr);
    return Rval;
}

SEXP _H5Pset_lzf( SEXP _plist_id ) {
    
    herr_t herr;
    
    int r = register_lzf();
    hid_t plist_id = INTEGER(_plist_id)[0];
    //herr = H5Pset_shuffle(plist_id);
    herr = H5Pset_filter(plist_id, H5PY_FILTER_LZF, H5Z_FLAG_OPTIONAL, 0, NULL);
    SEXP Rval = ScalarInteger(herr);
    
    htri_t avail = H5Zfilter_avail(H5PY_FILTER_LZF);
    unsigned filter_config;
    if (avail) {
        herr = H5Zget_filter_info (H5PY_FILTER_LZF, &filter_config);
        if ( (filter_config & H5Z_FILTER_CONFIG_ENCODE_ENABLED) && 
             (filter_config & H5Z_FILTER_CONFIG_DECODE_ENABLED) ) 
            Rprintf ("lzf filter is available for encoding and decoding.\n");
    }
    
    return Rval;
}

/*
SEXP _H5Pset_lz4( SEXP _plist_id ) {
    
    herr_t herr;
    const unsigned int cd_values[1] = {3};
    
    hid_t plist_id = INTEGER(_plist_id)[0];
    //herr = H5Pset_shuffle(plist_id);
    herr = H5Pset_filter(plist_id, H5Z_FILTER_LZ4, H5Z_FLAG_OPTIONAL, (size_t)1, cd_values);
    SEXP Rval = ScalarInteger(herr);
    
    htri_t avail = H5Zfilter_avail(H5Z_FILTER_LZ4);
    herr_t status;
    unsigned filter_config;
    if (avail) {
        status = H5Zget_filter_info (H5Z_FILTER_LZ4, &filter_config);
        if ( (filter_config & H5Z_FILTER_CONFIG_ENCODE_ENABLED) && 
             (filter_config & H5Z_FILTER_CONFIG_DECODE_ENABLED) ) 
            Rprintf ("lz4 filter is available for encoding and decoding.\n");
    }    
    
    return Rval;
}
*/

R_CallMethodDef callMethods[] = {
    {"_H5Pset_lzf", (DL_FUNC) &_H5Pset_lzf, 1},
    {NULL, NULL, 0}
};

void R_init_hdf5Filters(DllInfo *info)
{
    R_registerRoutines(info, NULL, callMethods, NULL, NULL);
}

