#include "libpluginhelper_string.h"
#include <cstring>

#ifdef _MSC_VER

#elif defined __GNUC__
    
#else
    #error "Unknown Complier. Please specify including file in the libpluginhelper_string.cpp"
#endif


LIBPLUGINHELPER_API int libpluginhelper_stricmp( const char * string1, const char * string2 )
{
    // compare two strings ignoring case
    #ifdef _MSC_VER
        return _stricmp(string1, string2);
    #elif defined __GNUC__
        return strcasecmp(string1, string2);
    #endif
}


LIBPLUGINHELPER_API int libpluginhelper_memicmp( const char * string1, const char * string2, size_t n )
{   
    // Compares characters in two buffers (case-insensitive)
    #ifdef _MSC_VER
        return _memicmp(string1, string2, n);
    #elif defined __GNUC__
        return strncasecmp(string1, string2, n);
    #endif
}


LIBPLUGINHELPER_API char * libpluginhelper_strtok( char * strToken, const char * strDelimit, char ** context )
{
    #ifdef _MSC_VER
        return strtok_s(strToken, strDelimit, context);
    #elif defined __GNUC__
        return strtok_r(strToken, strDelimit, context);
    #endif
}
