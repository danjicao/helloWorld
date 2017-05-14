#include "libpluginhelper_time.h"

#ifdef _MSC_VER

#elif defined __GNUC__
    
#else
    #error "Unknown Complier. Please specify including file in the libpluginhelper_time.cpp"
#endif


LIBPLUGINHELPER_API int libpluginhelper_ftime( libpluginhelper_timeb_t * timeptr )
{
    // This function returns the current time as seconds and milliseconds
    // since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).

    #ifdef _MSC_VER
        if ( 0 != _ftime_s(timeptr) )
        {
            //assert(0);
        }
        
        return 0;
    #elif defined __GNUC__
        return ftime(timeptr);
    #endif
}


LIBPLUGINHELPER_API struct tm * libpluginhelper_localtime( const time_t *timep, struct tm * result )
{
    #ifdef _MSC_VER
        if ( 0 == localtime_s(result, timep) )
        {
            return result;
        }

        return NULL;
    #elif defined __GNUC__
        return localtime_r(timep, result);
    #endif
}


LIBPLUGINHELPER_API bool libpluginhelper_getFileTime( FILETIME * ftTime )
{
    if ( NULL == ftTime )
    {
        return false;
    }

    #ifdef _MSC_VER
        GetSystemTimeAsFileTime(ftTime);
        return true;
    #elif defined __GNUC__
        // the windows epoch starts 1601-01-01T00:00:00Z (UTC). 
        // It's 11644473600 seconds before the UNIX/Linux epoch 1970-01-01T00:00:00Z (UTC).
        libpluginhelper_timeb_t tp;
        libpluginhelper_ftime(&tp);
        
        ftTime->dwLowDateTime  = tp.millitm /* 10^-3 sec */ * 10000LL;      // 10^-7 sec
        ftTime->dwHighDateTime = tp.time - 11644473600LL;                   // sec
        
        return false;
    #endif
}


LIBPLUGINHELPER_API bool libpluginhelper_getLocalTime( SYSTEMTIME * stTime )
{
    if ( NULL == stTime )
    {
        return false;
    }

    #ifdef _MSC_VER
        GetLocalTime(stTime);
        return true;
    #elif defined __GNUC__
        libpluginhelper_timeb_t tp;
        struct tm stm;
        libpluginhelper_ftime(&tp);
        time_t sec = tp.time + tp.timezone * 60;
        if ( NULL != libpluginhelper_localtime(&sec, &stm) ) 
        {
            stTime->wYear           = stm.tm_year + 1900;
            stTime->wMonth          = stm.tm_mon  + 1;
            stTime->wDayOfWeek      = stm.tm_wday;
            stTime->wDay            = stm.tm_mday;
            stTime->wHour           = stm.tm_hour;
            stTime->wMinute         = stm.tm_min;
            stTime->wSecond         = stm.tm_sec;
            stTime->wMilliseconds   = tp.millitm;      
            
            return true;
        }
        
        return false;
    #endif
}


LIBPLUGINHELPER_API bool libpluginhelper_getSystemTime( SYSTEMTIME * stTime )
{
    // UTC
    if ( NULL == stTime )
    {
        return false;
    }

    #ifdef _MSC_VER
        GetSystemTime(stTime);
        return true;
    #elif defined __GNUC__
        libpluginhelper_timeb_t tp;
        struct tm stm;
        libpluginhelper_ftime(&tp);
        if ( NULL != libpluginhelper_localtime(&tp.time, &stm) )
        {        
            stTime->wYear           = stm.tm_year + 1900;
            stTime->wMonth          = stm.tm_mon  + 1;
            stTime->wDayOfWeek      = stm.tm_wday;
            stTime->wDay            = stm.tm_mday;
            stTime->wHour           = stm.tm_hour;
            stTime->wMinute         = stm.tm_min;
            stTime->wSecond         = stm.tm_sec;
            stTime->wMilliseconds   = tp.millitm;      
            
            return true;
        }
        
        return false;
    #endif
}


LIBPLUGINHELPER_API bool libpluginhelper_FileTimeToSystemTime( const FILETIME * lpFileTime,  SYSTEMTIME * lpSystemTime )
{
    #ifdef _MSC_VER
        return FALSE != FileTimeToSystemTime( lpFileTime, lpSystemTime );
    #elif defined __GNUC__
        if ( NULL == lpSystemTime || NULL == lpFileTime )
        {
            return false;
        }
        
        int64_t  clock = (static_cast<int64_t>(lpFileTime->dwHighDateTime) << 32) | lpFileTime->dwLowDateTime;   
        time_t    t  = ((time_t)(clock - 116444736000000000LL) / 10000000LL);   
        struct tm stm;
        gmtime_r(&t, &stm);
        lpSystemTime->wYear         = stm.tm_year + 1900;
        lpSystemTime->wMonth        = stm.tm_mon + 1; 
        lpSystemTime->wDayOfWeek    = stm.tm_wday;
        lpSystemTime->wDay          = stm.tm_mday;
        lpSystemTime->wHour         = stm.tm_hour;
        lpSystemTime->wMinute       = stm.tm_min;
        lpSystemTime->wSecond       = stm.tm_sec;
        lpSystemTime->wMilliseconds = lpFileTime->dwLowDateTime / 1000;
        return true;
    #endif
}


LIBPLUGINHELPER_API bool libpluginhelper_SystemTimeToFileTime( const SYSTEMTIME * lpSystemTime, FILETIME * lpFileTime )
{
    #ifdef _MSC_VER
        return FALSE != SystemTimeToFileTime( lpSystemTime, lpFileTime );
    #elif defined __GNUC__
        if ( NULL == lpSystemTime || NULL == lpFileTime )
        {
            return false;
        }
        
        libpluginhelper_timeb_t tp;
        libpluginhelper_ftime(&tp);

        struct tm stm;
        stm.tm_year  = lpSystemTime->wYear - 1900;
        stm.tm_mon   = lpSystemTime->wMonth - 1;
        stm.tm_mday  = lpSystemTime->wDay;
        stm.tm_wday  = lpSystemTime->wDayOfWeek;
        stm.tm_hour  = lpSystemTime->wHour;
        stm.tm_min   = lpSystemTime->wMinute;
        stm.tm_sec   = lpSystemTime->wSecond;
        stm.tm_isdst = tp.dstflag;
        time_t clock = mktime(&stm); 
        clock -= tp.timezone * 60;

        int64_t t = static_cast<int64_t>(clock) * 10000000LL + 116444736000000000LL;
        t = t + (lpSystemTime->wMilliseconds/*10^-3 sec*/  * 1000);
        lpFileTime->dwLowDateTime = static_cast<uint32_t>(t);
        lpFileTime->dwHighDateTime = t >> 32;
        return true;
    #endif
}
