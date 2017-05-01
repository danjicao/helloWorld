#ifndef libexample_h_
#define libexample_h_


#if defined(LIBEXAMPLE_EXPORTS) && defined(LIBEXAMPLE_STATIC)
    #error "The preprocessor definitions of LIBEXAMPLE_EXPORTS and LIBEXAMPLE_STATIC can only be used individually"
#elif defined(LIBEXAMPLE_STATIC)
    #pragma message("Using static library libexample.")
    #define LIBEXAMPLE_API
    #define LIBEXAMPLE_LOCAL
#elif defined(LIBEXAMPLE_EXPORTS)
    #pragma message("Exporting library libexample.")
    #ifdef _MSC_VER
        #define LIBEXAMPLE_API __declspec(dllexport)
        #define LIBEXAMPLE_LOCAL
    #elif defined __GNUC__
        #if __GNUC__ >= 4
            #define LIBEXAMPLE_API __attribute__ ((visibility ("default")))
            #define LIBEXAMPLE_LOCAL __attribute__ ((visibility ("hidden")))
        #else
            #define LIBEXAMPLE_API
            #define LIBEXAMPLE_LOCAL
        #endif
    #else
        #error "Unknown Complier. Please specify incluing file in the libexample.h."
    #endif
#else
    #pragma message("Importing library libexample.")
    #ifdef _MSC_VER
        #define LIBEXAMPLE_API __declspec(dllimport)
        #define LIBEXAMPLE_LOCAL
    #elif defined __GNUC__
        #define LIBEXAMPLE_API
        #define LIBEXAMPLE_LOCAL
    #else
        #error "Unknown Complier. Please specify incluing file in the libexample.h."
    #endif
#endif


#include "libplugins_api.h"


#ifdef __cplusplus
extern "C" {
#endif


PLUGIN_APIS_DECLARATION(LIBEXAMPLE_API, libexample)


#ifdef __cplusplus
}   // end of extern "C" {
#endif
#endif // end of #ifndef libexample_h_

