#ifndef libsysinfo_h_
#define libsysinfo_h_


#if defined(LIBSYSINFO_EXPORTS) && defined(LIBSYSINFO_STATIC)
    #error "The preprocessor definitions of LIBSYSINFO_EXPORTS and LIBSYSINFO_STATIC can only be used individually"
#elif defined(LIBSYSINFO_STATIC)
    #pragma message("Using static library libsysinfo.")
    #define LIBSYSINFO_API
    #define LIBSYSINFO_LOCAL
#elif defined(LIBSYSINFO_EXPORTS)
    #pragma message("Exporting library libsysinfo.")
    #ifdef _MSC_VER
        #define LIBSYSINFO_API __declspec(dllexport)
        #define LIBSYSINFO_LOCAL
    #elif defined __GNUC__
        #if __GNUC__ >= 4
            #define LIBSYSINFO_API __attribute__ ((visibility ("default")))
            #define LIBSYSINFO_LOCAL  __attribute__ ((visibility ("hidden")))
        #else
            #define LIBSYSINFO_API
            #define LIBSYSINFO_LOCAL
        #endif
    #else
        #error "Unknown Complier. Please specify including file in the libsysinfo.h."
    #endif
#else
    #pragma message("Importing library libsysinfo.")
    #ifdef _MSC_VER
        #define LIBSYSINFO_API __declspec(dllimport)
        #define LIBSYSINFO_LOCAL
    #elif defined __GNUC__
        #define LIBSYSINFO_API
        #define LIBSYSINFO_LOCAL
    #else
        #error "Unknown Complier. Please specify including file in the libsysinfo.h."
    #endif
#endif

#include "libplugins_api.h"


#ifdef __cplusplus
extern "C" {
#endif


PLUGIN_INFO_APIS_DECLARATION(LIBSYSINFO_API, libsysinfo)


LIBSYSINFO_API void libsysinfo_printCompliedInfo ( void );

typedef enum {
  ENDIAN_UNKNOWN,
  ENDIAN_BIG,
  ENDIAN_LITTLE,
  ENDIAN_BIG_WORD,   /* Middle-endian, Honeywell 316 style */
  ENDIAN_LITTLE_WORD /* Middle-endian, PDP-11 style */
}LIBSYSINFO_ENDIAN_TYPE;

LIBSYSINFO_API LIBSYSINFO_ENDIAN_TYPE libsysinfo_getByteOrderType ( void );
LIBSYSINFO_API void libsysinfo_printByteOrderType ( void );

LIBSYSINFO_API int libsysinfo_isCharSigned ( void );

LIBSYSINFO_API const char * libsysinfo_getOsInfo ( void );



#ifdef __cplusplus
}   // end of extern "C" {
#endif
#endif // end of #ifndef libsysinfo_h_

