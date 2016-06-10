#ifndef hello_h_
#define hello_h_


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
        #error "Unknown Complier. Please specify incluing file in the hello.h."
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
        #error "Unknown Complier. Please specify incluing file in the hello.h."
    #endif
#endif


LIBHELLO_API void helloTo ( const char * helloToWho );
LIBHELLO_LOCAL void HiddenMe( void );

#endif // end of #ifndef hello_h_

