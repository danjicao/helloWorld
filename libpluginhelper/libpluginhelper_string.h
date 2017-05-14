#ifndef libpluginhelper_string_h_
#define libpluginhelper_string_h_


#include "libpluginhelper.h"
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


LIBPLUGINHELPER_API int libpluginhelper_stricmp( const char * string1, const char * string2 );
LIBPLUGINHELPER_API int libpluginhelper_memicmp( const char * string1, const char * string2, size_t n );
LIBPLUGINHELPER_API char * libpluginhelper_strtok( char * strToken, const char * strDelimit, char ** context );


#ifdef __cplusplus
}   // end of extern "C" {
#endif
#endif  // end of #ifndef libpluginhelper_string_h_

