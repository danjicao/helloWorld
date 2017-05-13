#ifndef libpluginhelper_h_
#define libpluginhelper_h_


#if defined(LIBPLUGINHELPER_EXPORTS) && defined(LIBPLUGINHELPER_STATIC)
    #error "The preprocessor definitions of LIBPLUGINHELPER_EXPORTS and LIBPLUGINHELPER_STATIC can only be used individually"
#elif defined(LIBPLUGINHELPER_STATIC)
    #pragma message("Using static library libpluginhelper.")
    #define LIBPLUGINHELPER_API
    #define LIBPLUGINHELPER_LOCAL
#elif defined(LIBPLUGINHELPER_EXPORTS)
    #pragma message("Exporting library libpluginhelper.")
    #ifdef _MSC_VER
        #define LIBPLUGINHELPER_API __declspec(dllexport)
        #define LIBPLUGINHELPER_LOCAL
    #elif defined __GNUC__
        #if __GNUC__ >= 4
            #define LIBPLUGINHELPER_API __attribute__ ((visibility ("default")))
            #define LIBPLUGINHELPER_LOCAL __attribute__ ((visibility ("hidden")))
        #else
            #define LIBPLUGINHELPER_API
            #define LIBPLUGINHELPER_LOCAL
        #endif
    #else
        #error "Unknown Complier. Please specify including file in the libpluginhelper.h."
    #endif
#else
    #pragma message("Importing library libpluginhelper.")
    #ifdef _MSC_VER
        #define LIBPLUGINHELPER_API __declspec(dllimport)
        #define LIBPLUGINHELPER_LOCAL
    #elif defined __GNUC__
        #define LIBPLUGINHELPER_API
        #define LIBPLUGINHELPER_LOCAL
    #else
        #error "Unknown Complier. Please specify including file in the libpluginhelper.h."
    #endif
#endif


#include "libplugins_api.h"


#ifdef __cplusplus
extern "C" {
#endif


PLUGIN_INFO_APIS_DECLARATION(LIBPLUGINHELPER_API, libpluginhelper)


#ifdef __cplusplus
}   // end of extern "C" {
#endif
#endif // end of #ifndef libpluginhelper_h_

