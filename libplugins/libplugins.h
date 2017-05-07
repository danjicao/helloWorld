#ifndef libplugins_h_
#define libplugins_h_


#if defined(LIBPLUGINS_EXPORTS) && defined(LIBPLUGINS_STATIC)
    #error "The preprocessor definitions of LIBPLUGINS_EXPORTS and LIBPLUGINS_STATIC can only be used individually"
#elif defined(LIBPLUGINS_STATIC)
    #pragma message("Using static library libplugins.")
    #define LIBPLUGINS_API
    #define LIBPLUGINS_LOCAL
#elif defined(LIBPLUGINS_EXPORTS)
    #pragma message("Exporting library libplugins.")
    #ifdef _MSC_VER
        #define LIBPLUGINS_API __declspec(dllexport)
        #define LIBPLUGINS_LOCAL
    #elif defined __GNUC__
        #if __GNUC__ >= 4
            #define LIBPLUGINS_API __attribute__ ((visibility ("default")))
            #define LIBPLUGINS_LOCAL __attribute__ ((visibility ("hidden")))
        #else
            #define LIBPLUGINS_API
            #define LIBPLUGINS_LOCAL
        #endif
    #else
        #error "Unknown Complier. Please specify including file in the libplugins.h."
    #endif
#else
    #pragma message("Importing library libplugins.")
    #ifdef _MSC_VER
        #define LIBPLUGINS_API __declspec(dllimport)
        #define LIBPLUGINS_LOCAL
    #elif defined __GNUC__
        #define LIBPLUGINS_API
        #define LIBPLUGINS_LOCAL
    #else
        #error "Unknown Complier. Please specify including file in the libplugins.h."
    #endif
#endif


#include "libplugins_api.h"


#ifdef __cplusplus
extern "C" {
#endif


PLUGIN_APIS_DECLARATION(LIBPLUGINS_API, libplugins)


#ifdef __cplusplus
}   // end of extern "C" {
#endif
#endif // end of #ifndef libplugins_h_

