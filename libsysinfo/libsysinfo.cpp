#include "libsysinfo.h"
#include "config.h"
#include <cstdio>
#include <cstdarg>
#include <stdint.h>

#ifdef __ANDROID__
    #include <android/api-level.h>
#endif


#if defined __FreeBSD__ || defined __FreeBSD_kernel__
    #include <sys/param.h>
    #include <osreldate.h>
#elif defined __NetBSD__ || defined __OpenBSD__ || defined __bsdi__ || defined __DragonFly__
    #include <sys/param.h>
#endif


namespace {

void print(const char * fmt, ...)
{
    va_list valist;
    va_start(valist, fmt);

    int res = vfprintf(stdout, fmt, valist);

    if ( res <= 0 )
    {
        // error
    }
    va_end (valist);
}

}    // end of namespace {


LIBSYSINFO_API void libsysinfo_printCompliedInfo ( void )
{
    // reference :
    // 1. http://sourceforge.net/p/predef/wiki/Compilers/
    // 2. http://www.cse.psu.edu/~dheller/cmpsc311/Lectures/Standards/CStandard/CStandard.c

    print(">>  Complied information:\n");
    print("    __DATE__=\"%s\"\n", __DATE__);
    print("    __TIME__=\"%s\"\n", __TIME__);

#if defined __APPLE__ && defined __MACH__
    #if defined __apple_build_version__
    print("    Target Host : Mac OS X (__apple_build_version__=%d)\n", __apple_build_version__);
    #else
    print("    Target Host : Mac OS X\n");
    #endif
#elif defined Macintosh || defined macintosh
    print("    Target Host : Mac OS 9\n");
#elif defined MSDOS || defined __MSDOS__ || defined _MSDOS || defined __DOS__
    print("    Target Host : MSDOS\n");
#elif defined __ANDROID__
    print("    Target Host : Android (%s)\n", __ANDROID_API__);
#elif defined __FreeBSD__ || defined __FreeBSD_kernel__
    print("    Target Host : FreeBSD (%s, %s, %s)\n", BSD, __FreeBSD__, __FreeBSD_version);
#elif defined __NetBSD__
    print("    Target Host : NetBSD (%s, %s)\n", BSD, __NetBSD_Version__);
#elif defined __OpenBSD__
    print("    Target Host : OpenBSD (%s)\n", BSD);
#elif defined __bsdi__ || defined __DragonFly__
    print("    Target Host : BSD (%s)\n", BSD);
#elif defined __gnu_linux__
    print("    Target Host : GNU/Linux\n");
#elif defined sun || defined __sun
    # if defined(__SVR4) || defined(__svr4__)
    print("    Target Host : Solaris\n");
    #else
    print("    Target Host : SunOS\n");
    #endif
#elif defined __unix__ || defined __unix
    print("    Target Host : UNIX\n");
#elif defined _WIN64
    print("    Target Host : Windows 64bits\n");
#elif defined _WIN32
    print("    Target Host : Windows 32bits\n");
#elif defined _WIN16
    print("    Target Host : Windows 16bits\n");
#else
    print("    Target Host : UNKNOWN\n");
#endif


#ifdef __embedded_cplusplus
    print("    __embedded_cplusplus : Embedded C++\n");
#elif defined(__cplusplus)
    #if __cplusplus >= 201402L
    print("    __cplusplus = \"%d\" : C++14 (ISO/IEC 14882:2011)\n", __cplusplus);
    #elif __cplusplus >= 201103L
    print("    __cplusplus = \"%d\" : C++11 (ISO/IEC 14882:2011)\n", __cplusplus);
    #elif __cplusplus >= 199711L
    print("    __cplusplus = \"%d\" : C++98 (ISO/IEC 14882:1998)\n", __cplusplus);
    #else
    print("    __cplusplus = \"%d\" : N/A\n", __cplusplus);
    #endif
#elif defined(__STDC__)
        print("    This is standard C.\n");

    #if (__STDC__ == 1)
        print("    The implementation is ISO-conforming.\n");
    #else
        print("    The implementation is not ISO-conforming.\n");
    #endif

    #if defined(__STDC_VERSION__)
        #if __STDC_VERSION__ >= 201112L
        print("    __STDC_VERSION__ = \"%ld\" : C11 (ISO/IEC 9899:2011)\n", __STDC_VERSION__);
        #elif __STDC_VERSION__ >= 199901L
        print("    __STDC_VERSION__ = \"%ld\" : C99 (ISO/IEC 9899:1999)\n", __STDC_VERSION__);
        #elif __STDC_VERSION__ >= 199409L
        print("    __STDC_VERSION__ = \"%ld\" : C94 (ISO/IEC 9899-1:1994)\n", __STDC_VERSION__);
        #else
        print("    __STDC_VERSION__ = \"%ld\" : C90 (ISO/IEC 9899:1990)\n", __STDC_VERSION__);
        #endif
        print("    __STDC_VERSION__ = \"%ld\" : C89\n", __STDC_VERSION__);
        print("    __STDC__ = \"%ld\"\n", __STDC__);
    #else
        print("    __STDC__ = \"%ld\" : C89 (ANSI X3.159-1989). __STDC_VERSION__ is not defined.\n", __STDC__);
    #endif
#elif defined(__OBJC__)
    print("    __OBJC__\n");
#else
    print("    Error! unknown language.\n");
#endif


#if defined(__STDC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
    #if defined(__STDC_HOSTED__)
        #if (__STDC_HOSTED__ == 1)
        print("  This is a hosted implementation.\n");
        #elif (__STDC_HOSTED__ == 0)
        print("  This is a freestanding implementation.\n");
        #else
        print("  __STDC_HOSTED__ = %d is an unexpected value.\n", __STDC_HOSTED__);
        #endif
    #else
    print("  __STDC_HOSTED__ is not defined.\n");
    print("    This should indicate hosted or freestanding implementation.\n");
    #endif

    #if defined(__STDC_ISO_10646__)
    print("  The wchar_t values conform to the ISO/IEC 10646 standard (Unicode) as of %ld.\n", __STDC_ISO_10646__);
    #else
    print("  __STDC_ISO_10646__ is not defined.\n");
    print("    The wchar_t values are implementation-defined.\n");
    #endif

    /* added in C99 Technical Corrigendum 3 */
    #if defined(__STDC_MB_MIGHT_NEQ_WC__)
        #if (__STDC_MB_MIGHT_NEQ_WC__ == 1)
        print("  Wide and multibyte characters might not have the same codes.\n");
        #else
        print("  __STDC_MB_MIGHT_NEQ_WC__ = %d is an unexpected value.\n", __STDC_MB_MIGHT_NEQ_WC__);
        #endif
    #else
    print("  __STDC_MB_MIGHT_NEQ_WC__ is not defined.\n");
    print("    Wide and multibyte characters should have the same codes.\n");
    #endif

    #if defined(__STDC_IEC_559__)
        #if (__STDC_IEC_559__ == 1)
        print("  The floating-point implementation conforms to Annex F (IEC 60559 standard).\n");
        #else
        print("  __STDC_IEC_559__ = %d is an unexpected value.\n", __STDC_IEC_559__);
        #endif
    #else
    print("  __STDC_IEC_559__ is not defined.\n");
    print("    The floating-point implementation does not conform to Annex F (IEC 60559 standard).\n");
    #endif

    #if defined(__STDC_IEC_559_COMPLEX__)
        #if (__STDC_IEC_559_COMPLEX__ == 1)
        print("  The complex arithmetic implementation conforms to Annex G (IEC 60559 standard).\n");
        #else
        print("  __STDC_IEC_559_COMPLEX__ = %d is an unexpected value.\n", __STDC_IEC_559_COMPLEX__);
        #endif
    #else
    print("  __STDC_IEC_559_COMPLEX__ is not defined.\n");
    print("    The complex arithmetic implementation does not conform to Annex G (IEC 60559 standard).\n");
    #endif
#endif

#if defined(__STDC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
    #if defined(__STDC_UTF_16__)
        #if (__STDC_UTF_16__ == 1)
        print("  The char16_t values are UTF-16 encoded.\n");
        #else
        print("  __STDC_UTF_16__ = %d is an unexpected value.\n", __STDC_UTF_16__);
        #endif
    #else
    print("  __STDC_UTF_16__ is not defined.\n");
    print("    The char16_t values are implementation-defined.\n");
    #endif

    #if defined(__STDC_UTF_32__)
        #if (__STDC_UTF_32__ == 1)
        print("  The char32_t values are UTF-32 encoded.\n");
        #else
        print("  __STDC_UTF_32__ = %d is an unexpected value.\n", __STDC_UTF_32__);
        #endif
    #else
    print("  __STDC_UTF_32__ is not defined.\n");
    print("    The char32_t values are implementation-defined.\n");
    #endif

    #if defined(__STDC_ANALYZABLE__)
        #if (__STDC_ANALYZABLE__ == 1)
        print("  The compiler conforms to the specifications in Annex L (Analyzability).\n");
        #else
        print("  __STDC_ANALYZABLE__ = %d is an unexpected value.\n", __STDC_ANALYZABLE__);
        #endif
    #else
    print("  __STDC_ANALYZABLE__ is not defined.\n");
    print("    The compiler does not conform to the specifications in Annex L (Analyzability).\n");
    #endif

    #if defined(__STDC_LIB_EXT1__)
    print("  The implementation supports the extensions defined in Annex K (Bounds-checking interfaces) as of %ld.\n", __STDC_LIB_EXT1__);
    #else
    print("  __STDC_LIB_EXT1__ is not defined.\n");
    print("    The implementation does not support the extensions defined in Annex K (Bounds-checking interfaces).\n");
    #endif

    #if defined(__STDC_NO_ATOMICS__)
        #if (__STDC_NO_ATOMICS__ == 1)
        print("  The implementation does not support atomic types.\n");
        #else
        print("  __STDC_NO_ATOMICS__ = %d is an unexpected value.\n", __STDC_NO_ATOMICS__);
        #endif
    #else
    // print("  __STDC_NO_ATOMICS__ is not defined.\n");
    print("  The implementation supports atomic types and <stdatomic.h>.\n");
    #endif

    #if defined(__STDC_NO_COMPLEX__)
        #if (__STDC_NO_COMPLEX__ == 1)
        print("  The implementation does not support complex types.\n");
        #else
        print("  __STDC_NO_COMPLEX__ = %d is an unexpected value.\n", __STDC_NO_COMPLEX__);
        #endif
    #if defined(__STDC_IEC_559_COMPLEX__)
    print("  However, __STDC_IEC_559_COMPLEX__ is defined, and it should not be.\n");
    #endif
    #else
    // print("  __STDC_NO_COMPLEX__ is not defined.\n");
    print("  The implementation supports complex types and <complex.h>.\n");
    #endif

    #if defined(__STDC_NO_THREADS__)
        #if (__STDC_NO_THREADS__ == 1)
        print("  The implementation does not support threads.\n");
        #else
        print("  __STDC_NO_THREADS__ = %d is an unexpected value.\n", __STDC_NO_THREADS__);
        #endif
    #else
    // print("  __STDC_NO_THREADS__ is not defined.\n");
    print("  The implementation supports threads and <threads.h>.\n");
    #endif

    #if defined(__STDC_NO_VLA__)
        #if (__STDC_NO_VLA__ == 1)
        print("  The implementation does not support variable length arrays.\n");
        #else
        print("  __STDC_NO_VLA__ = %d is an unexpected value.\n", __STDC_NO_VLA__);
        #endif
    #else
    // print("  __STDC_NO_VLA__ is not defined.\n");
    print("  The implementation supports variable length arrays.\n");
    #endif
#endif


#ifdef __BORLANDC__
    #if __BORLANDC__ >= 0x660
    print("    __BORLANDC__ = \"%ld\" : C++ Builder XE4\n", __BORLANDC__);
    #elif __BORLANDC__ >= 0x650
    print("    __BORLANDC__ = \"%ld\" : C++ Builder XE3\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x640
    print("    __BORLANDC__ = \"%ld\" : C++ Builder XE2\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x630
    print("    __BORLANDC__ = \"%ld\" : C++ Builder XE\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x621
    print("    __BORLANDC__ = \"%ld\" : C++ Builder 2010\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x613
    print("    __BORLANDC__ = \"%ld\" : C++ Builder 2009\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x590
    print("    __BORLANDC__ = \"%ld\" : C++ Builder 2007\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x570
    print("    __BORLANDC__ = \"%ld\" : C++ Builder 2006\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x562
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 5.6.4\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x551
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 5.51\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x550
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 5.5 / C++ Builder 5.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x540
    print("    __BORLANDC__ = \"%ld\" : C++ Builder 4.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x530
    print("    __BORLANDC__ = \"%ld\" : C++ Builder 3.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x520
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 5.02 / C++ Builder 1.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x500
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 5.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x452
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 4.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x410
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 3.1\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x400
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 3.0\n",__BORLANDC__);
    #elif __BORLANDC__ >= 0x200
    print("    __BORLANDC__ = \"%ld\" : Borland C++ Builder 2.0\n",__BORLANDC__);
    #else
    print("    __BORLANDC__\n");
    #endif
#endif


#if defined __clang__
    print("    __clang__ : %d.%d.%d\n", __clang_major__,  __clang_minor__, __clang_patchlevel__);
#endif


#if defined __llvm__
    print("    __llvm__ : %d\n", __llvm__);
#endif


#if defined __GNUC__
    #ifdef __GNUC_PATCHLEVEL__
    print("    __GNUC__ : %d.%d.%d\n", __GNUC__,  __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #else
    print("    __GNUC__ : %d.%d\n", __GNUC__,  __GNUC_MINOR__);
    #endif

    //print("    GNU libc version: %s\n", gnu_get_libc_version());
    //print("    GNU libc release: %s\n", gnu_get_libc_release());
#endif


#if defined __INTEL_COMPILER
    print("    __INTEL_COMPILER : %s (__INTEL_COMPILER_BUILD_DATE=%d)\n", __INTEL_COMPILER, __INTEL_COMPILER_BUILD_DATE);
#endif


#if defined __TURBOC__
    print("    __TURBOC__ : %d\n", __TURBOC__);
#endif


#if defined _MSC_VER // Microsoft Visual C++
    #ifdef _MSC_FULL_VER
    print("    _MSC_FULL_VER = \"%ld\"\n", _MSC_FULL_VER);
    #endif

    #if _MSC_VER >= 1910
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 15.0 (2017)\n", _MSC_VER); // _MSC_FULL_VER == 191025017
    #elif _MSC_VER >= 1900
        #if _MSC_FULL_VER >= 190024210L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 14.0 (2015 Update 3)\n", _MSC_VER);
        #elif _MSC_FULL_VER >= 190023918L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 14.0 (2015 Update 2)\n", _MSC_VER);
        #elif _MSC_FULL_VER >= 190023506L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 14.0 (2015 Update 1)\n", _MSC_VER);
        #elif _MSC_FULL_VER >= 190023026L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 14.0 (2015)\n", _MSC_VER);
        #else
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 14.0 (2015) Unknown\n", _MSC_VER);
        #endif
    #elif _MSC_VER >= 1800
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 12.0 (2013)\n", _MSC_VER); // _MSC_FULL_VER == 180021005
    #elif _MSC_VER >= 1700
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 11.0 (2012)\n", _MSC_VER); // _MSC_FULL_VER == 170050727
    #elif _MSC_VER >= 1600
        #if _MSC_FULL_VER >= 160040219L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 10.0 (2010) SP1\n", _MSC_VER);
        #elif _MSC_FULL_VER >= 160030319L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 10.0 (2010)\n", _MSC_VER);
        #else
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 10.0 (2010) Unknown\n", _MSC_VER);
        #endif
    #elif _MSC_VER >= 1500
        #if _MSC_FULL_VER >= 150030729L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 9.0 SP1\n", _MSC_VER);
        #elif _MSC_FULL_VER >= 150021022L
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 9.0 (2008)\n", _MSC_VER);
        #else
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 9.0 *\n", _MSC_VER);
        #endif
    #elif _MSC_VER >= 1400
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 8.0 (2005)\n", _MSC_VER);
    #elif _MSC_VER >= 1310
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 7.1 (2003)\n", _MSC_VER);
    #elif _MSC_VER >= 1300
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 7.0\n", _MSC_VER);
    #elif _MSC_VER >= 1200
        #ifdef _MSC_FULL_VER
            #if _MSC_FULL_VER >= 12008804L
            print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 6.0 SP6\n", _MSC_VER);
            #else
            print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 6.0 *\n", _MSC_VER);
            #endif
        #else
        print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 6.0\n", _MSC_VER);
        #endif
    #elif _MSC_VER >= 1100
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 5.0\n", _MSC_VER);
    #elif _MSC_VER >= 1020
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 4.2\n", _MSC_VER);
    #elif _MSC_VER >= 1000
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 4.0\n", _MSC_VER);
    #elif _MSC_VER >= 900
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 3.0\n", _MSC_VER);
    #elif _MSC_VER >= 800
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ 1.0\n", _MSC_VER);
    #else
    print("    _MSC_VER = \"%ld\" : Microsoft Visual C++ (Unknown version)\n", _MSC_VER);
    #endif
#endif


#if defined __MINGW32__
    print("    __MINGW32__ = \"%ld\" : MinGW32 %d.%d\n", __MINGW32_MAJOR_VERSION, __MINGW32_MINOR_VERSION);
    #ifdef __MINGW64__
    print("    __MINGW64__ = \"%ld\" : MinGW-w64 64 Bit %d.%d\n", __MINGW64_VERSION_MAJOR, __MINGW64_VERSION_MINOR);
    #else
    print("    __MINGW64__ = \"%ld\" : MinGW-w64 32 Bit %d.%d\n", __MINGW64_VERSION_MAJOR, __MINGW64_VERSION_MINOR);
    #endif
#endif

#ifdef __CC_ARM
    print("    ARM Compiler : __CC_ARM, __ARMCC_VERSION=\"%ld\"\n", __ARMCC_VERSION); // VRPBBB: V = Version / R = Revision / P = Patch / BBB = Build
#endif
}



LIBSYSINFO_API LIBSYSINFO_ENDIAN_TYPE libsysinfo_getByteOrderType ( void ) {
    // https://sourceforge.net/p/predef/wiki/Endianness/
    union {
        uint32_t value;
        uint8_t data[sizeof(uint32_t)];
    } number;

    number.data[0] = 0x00;
    number.data[1] = 0x01;
    number.data[2] = 0x02;
    number.data[3] = 0x03;

    switch (number.value)
    {
    case UINT32_C(0x00010203):
        return ENDIAN_BIG;
    case UINT32_C(0x03020100):
        return ENDIAN_LITTLE;
    case UINT32_C(0x02030001):
        return ENDIAN_BIG_WORD;
    case UINT32_C(0x01000302):
        return ENDIAN_LITTLE_WORD;
    default:
        fprintf(stderr, "Error: unknown byte order: %X\n", number.value);
        return ENDIAN_UNKNOWN;
    }
}

LIBSYSINFO_API void libsysinfo_printByteOrderType ( void ) {
    LIBSYSINFO_ENDIAN_TYPE type = libsysinfo_getByteOrderType();

    switch(type) {
        case ENDIAN_BIG:
            printf("Byte order: big-endian\n"); // network byte order
            break;
        case ENDIAN_LITTLE:
            printf("Byte order: little-endian\n");
            break;
        case ENDIAN_BIG_WORD:
            printf("Byte order: Honeywell 316 style endian\n");
            break;
        case ENDIAN_LITTLE_WORD:
            printf("Byte order: PDP-11 style endian\n");
            break;
        default:
            printf("Byte order: unknown\n");
            break;
    }
}


LIBSYSINFO_API int libsysinfo_isCharSigned ( void ) {
    char negativeOne = (char) -1;
    return (negativeOne < 0)?1:0;
}


LIBSYSINFO_API const char * libsysinfo_get_verion( void ) {
    return PROJECT_VERSION;
}


LIBSYSINFO_API const char * libsysinfo_get_revision( void ) {
    return PROJECT_GIT_REVISION;
}

