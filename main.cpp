#include <stdio.h>
#include "config.h"
#include "libhello/libhello.h"
#include "libsysinfo/libsysinfo.h"

static void beforeMain( void );
static void afterMain( void );


#ifdef _MSC_VER
    #include <stdlib.h>
    #define CCALL __cdecl
    #pragma section(".CRT$XCU",read)

    static void __cdecl AFTER_MAIN( void )
    {
        afterMain();
        system("PAUSE");
    }

    static void __cdecl BEFORE_MAIN( void )
    {
        beforeMain();
        atexit(AFTER_MAIN);
    }

    __declspec(allocate(".CRT$XCU")) void (__cdecl * FP_BEFORE_MAIN)( void ) = BEFORE_MAIN;


#elif defined(__GNUC__)
    #define CCALL
    static __attribute__((destructor)) void AFTER_MAIN( void )
    {
        afterMain();
    }

    static __attribute__((constructor)) void BEFORE_MAIN( void )
    {
        beforeMain();
    }


#else
    #error "Unknown Complier. Please specify incluing file in the main.cpp."
#endif


void DoSomethingInMainBody( void )
{
    libhello_helloTo("World");
    //libhello_HiddenMe(); // Hence, HiddenMe should NOT be called.
}


int CCALL main ( int argc, /*const*/ char * argv[], /*const*/ char* /*const*/ * envp )
{
    printf("%s ver. %s, rev. %s\n", PROJECT, PROJECT_VERSION, PROJECT_GIT_REVISION);
    printf("libsysinfo ver. %s, rev. %s\n", libsysinfo_get_verion(), libsysinfo_get_revision());
    printf(">>  arguments:\n");
    printf("    argc=%d\n", argc);
    for( int i = 0; i < argc; ++i )
    {
        printf( "    argv[%2d] = \"%s\"\n", i, argv[i] );
    }

    printf(">>  environment variables:\n");
    for (const char* const* env = envp; *env != NULL; ++env)
    {
        printf("    %s\n", *env);
    }

    libsysinfo_printCompliedInfo();

    printf(">>  Appliction Begin\n");

    DoSomethingInMainBody();

    printf(">>  Appliction Finish\n");
    return 0;
}


void beforeMain( void )
{
    printf(">>  Before Main\n");
}


void afterMain( void )
{
    printf(">>  After Main\n");
}


