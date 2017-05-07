#ifndef LIBHELLO_H_
#define LIBHELLO_H_


#if defined(LIBHELLO_EXPORTS) && defined(LIBHELLO_STATIC)
    #error "The preprocessor definitions of LIBHELLO_EXPORTS and LIBHELLO_STATIC can only be used individually"
#elif defined(LIBHELLO_STATIC)
    #pragma message("Using static library libhello.")
    #define LIBHELLO_API
    #define LIBHELLO_LOCAL
#elif defined(LIBHELLO_EXPORTS)
    #pragma message("Exporting library libhello.")
    #ifdef _MSC_VER
        #define LIBHELLO_API __declspec(dllexport)
        #define LIBHELLO_LOCAL
    #elif defined __GNUC__
        #if __GNUC__ >= 4
            #define LIBHELLO_API __attribute__ ((visibility ("default")))
            #define LIBHELLO_LOCAL  __attribute__ ((visibility ("hidden")))
        #else
            #define LIBHELLO_API
            #define LIBHELLO_LOCAL
        #endif
    #else
        #error "Unknown Complier. Please specify including file in the libhello.h."
    #endif
#else
    #pragma message("Importing library libhello.")
    #ifdef _MSC_VER
        #define LIBHELLO_API __declspec(dllimport)
        #define LIBHELLO_LOCAL
    #elif defined __GNUC__
        #define LIBHELLO_API
        #define LIBHELLO_LOCAL
    #else
        #error "Unknown Complier. Please specify including file in the libhello.h."
    #endif
#endif


LIBHELLO_API void libhello_helloTo ( const char * helloToWho );
LIBHELLO_LOCAL void libhello_HiddenMe( void );
LIBHELLO_API const char * libhello_get_verion( void );
LIBHELLO_API const char * libhello_get_revision( void );

#endif // end of #ifndef LIBHELLO_H_

