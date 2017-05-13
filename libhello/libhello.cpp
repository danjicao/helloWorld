#include "libhello.h"
#include "config.h"
#include <cstdio>


PLUGIN_INFO_APIS_DEFINITION(LIBHELLO_API, libhello, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_VERSION_MAJOR, PROJECT_BUILD_TIME)


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

