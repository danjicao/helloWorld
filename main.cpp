#include <stdio.h>

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
    printf("Hello World!!\n");
}


int CCALL main ( int argc, /*const*/ char * argv[], /*const*/ char* /*const*/ * envp )
{
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


