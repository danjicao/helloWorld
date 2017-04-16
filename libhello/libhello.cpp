#include "libhello.h"
#include "config.h"
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


LIBHELLO_API const char * libhello_get_verion( void ) {
    return PROJECT_VERSION;
}


LIBHELLO_API const char * libhello_get_revision( void ) {
    return PROJECT_GIT_REVISION;
}

