#ifndef libpluginhelper_time_h_
#define libpluginhelper_time_h_


#include "libpluginhelper.h"


#ifdef _MSC_VER
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>
    #include <time.h>
    #include <sys/timeb.h>
    typedef struct _timeb libpluginhelper_timeb_t;

#elif defined __GNUC__
    #include <stdint.h>
    #include <time.h>
    #include <sys/timeb.h>
    typedef struct timeb libpluginhelper_timeb_t;


    #pragma pack(push,1)
    typedef struct _FILETIME {
        uint32_t dwLowDateTime;
        uint32_t dwHighDateTime;
    } FILETIME, *PFILETIME;
    #pragma pack(pop)

    #pragma pack(push,1)
    typedef struct _SYSTEMTIME {
        uint16_t wYear;
        uint16_t wMonth;
        uint16_t wDayOfWeek;
        uint16_t wDay;
        uint16_t wHour;
        uint16_t wMinute;
        uint16_t wSecond;
        uint16_t wMilliseconds;
    } SYSTEMTIME, *PSYSTEMTIME;
    #pragma pack(pop)


#else
    #error "Unknown Complier. Please specify including file in the libpluginhelper_time.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif


LIBPLUGINHELPER_API int libpluginhelper_ftime( libpluginhelper_timeb_t * timeptr );
LIBPLUGINHELPER_API struct tm * libpluginhelper_localtime( const time_t *timep, struct tm * result );
LIBPLUGINHELPER_API bool libpluginhelper_getFileTime( FILETIME * ftTime );
LIBPLUGINHELPER_API bool libpluginhelper_getLocalTime( SYSTEMTIME * stTime );
LIBPLUGINHELPER_API bool libpluginhelper_getSystemTime( SYSTEMTIME * stTime );
LIBPLUGINHELPER_API bool libpluginhelper_FileTimeToSystemTime( const FILETIME * lpFileTime,  SYSTEMTIME * lpSystemTime );
LIBPLUGINHELPER_API bool libpluginhelper_SystemTimeToFileTime( const SYSTEMTIME * lpSystemTime, FILETIME * lpFileTime );


#ifdef __cplusplus
}   // end of extern "C" {
#endif
#endif  // end of #ifndef libpluginhelper_time_h_
