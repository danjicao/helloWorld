#include "libhello.h"
#include <cstdio>

LIBHELLO_API void libhello_helloTo ( const char * helloToWho )
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


LIBHELLO_LOCAL void libhello_HiddenMe( void )
{
    printf("I am hidden.\n");
}

