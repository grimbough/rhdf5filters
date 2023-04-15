
#ifndef VBZ_HDF_PLUGIN_EXPORT_H
#define VBZ_HDF_PLUGIN_EXPORT_H

#ifdef VBZ_HDF_PLUGIN_STATIC_DEFINE
#  define VBZ_HDF_PLUGIN_EXPORT
#  define VBZ_HDF_PLUGIN_NO_EXPORT
#else
#  ifndef VBZ_HDF_PLUGIN_EXPORT
#    ifdef vbz_hdf_plugin_EXPORTS
        /* We are building this library */
#      define VBZ_HDF_PLUGIN_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VBZ_HDF_PLUGIN_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VBZ_HDF_PLUGIN_NO_EXPORT
#    define VBZ_HDF_PLUGIN_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VBZ_HDF_PLUGIN_DEPRECATED
#  define VBZ_HDF_PLUGIN_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VBZ_HDF_PLUGIN_DEPRECATED_EXPORT
#  define VBZ_HDF_PLUGIN_DEPRECATED_EXPORT VBZ_HDF_PLUGIN_EXPORT VBZ_HDF_PLUGIN_DEPRECATED
#endif

#ifndef VBZ_HDF_PLUGIN_DEPRECATED_NO_EXPORT
#  define VBZ_HDF_PLUGIN_DEPRECATED_NO_EXPORT VBZ_HDF_PLUGIN_NO_EXPORT VBZ_HDF_PLUGIN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VBZ_HDF_PLUGIN_NO_DEPRECATED
#    define VBZ_HDF_PLUGIN_NO_DEPRECATED
#  endif
#endif

#endif /* VBZ_HDF_PLUGIN_EXPORT_H */
