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
        #error "Unknown Complier. Please specify incluing file in the libsysinfo.h."
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
        #error "Unknown Complier. Please specify incluing file in the libsysinfo.h."
    #endif
#endif


LIBSYSINFO_API void libsysinfo_printCompliedInfo ( void );
LIBSYSINFO_API const char * libsysinfo_get_verion( void );
LIBSYSINFO_API const char * libsysinfo_get_revision( void );

#endif // end of #ifndef libsysinfo_h_

