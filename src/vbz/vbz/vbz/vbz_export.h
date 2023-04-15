
#ifndef VBZ_EXPORT_H
#define VBZ_EXPORT_H

#ifdef VBZ_STATIC_DEFINE
#  define VBZ_EXPORT
#  define VBZ_NO_EXPORT
#else
#  ifndef VBZ_EXPORT
#    ifdef vbz_EXPORTS
        /* We are building this library */
#      define VBZ_EXPORT 
#    else
        /* We are using this library */
#      define VBZ_EXPORT 
#    endif
#  endif

#  ifndef VBZ_NO_EXPORT
#    define VBZ_NO_EXPORT 
#  endif
#endif

#ifndef VBZ_DEPRECATED
#  define VBZ_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VBZ_DEPRECATED_EXPORT
#  define VBZ_DEPRECATED_EXPORT VBZ_EXPORT VBZ_DEPRECATED
#endif

#ifndef VBZ_DEPRECATED_NO_EXPORT
#  define VBZ_DEPRECATED_NO_EXPORT VBZ_NO_EXPORT VBZ_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VBZ_NO_DEPRECATED
#    define VBZ_NO_DEPRECATED
#  endif
#endif

#endif /* VBZ_EXPORT_H */
