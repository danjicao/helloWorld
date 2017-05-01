#include <stdio.h>
#include "config.h"
#include "libhello/libhello.h"
#include "libsysinfo/libsysinfo.h"

#ifdef ENABLE_PLUGINS
#include "libplugins/libplugins.h"
#endif


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


#ifdef ENABLE_PLUGINS
int PluginEventHandler( const char * ) {

    return 0;
}
#endif


int CCALL main ( int argc, /*const*/ char * argv[], /*const*/ char* /*const*/ * envp )
{
    printf("%s ver. %s, rev. %s (%s)\n", PROJECT, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_BUILD_TIME);
    printf("libsysinfo ver. %s, rev. %s\n", libsysinfo_get_verion(), libsysinfo_get_revision());
    printf("libhello   ver. %s, rev. %s\n", libhello_get_verion(), libhello_get_revision());

    #ifdef ENABLE_PLUGINS
    printf("%10s ver. %s, rev. %s, sover. %s (%s)\n", libplugins_get_plugin_name(), libplugins_get_plugin_version(), libplugins_get_plugin_revision(), libplugins_get_plugin_soversion(), libplugins_get_plugin_buildtime());
    #endif

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

    #ifdef ENABLE_PLUGINS
    libplugins_init("", PluginEventHandler);
    libplugins_deinit();
    #endif
    
    libsysinfo_printCompliedInfo();
    libsysinfo_printByteOrderType();
    printf("libsysinfo_isCharSigned=%d\n", libsysinfo_isCharSigned());

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


