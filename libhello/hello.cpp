#include "hello.h"
#include <cstdio>

LIBHELLO_API void helloTo ( const char * helloToWho )
{
    if ( helloToWho )
    {
        printf ("Hello, %s.\n", helloToWho );
    }
    else
    {
        printf ("Hello!\n" );
    }
}

