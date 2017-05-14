#include "libpluginhelper_assert.h"


#ifdef _MSC_VER
    #include <assert.h>
    
#elif defined __GNUC__
    #include <cassert>
    
#else
    #error "Unknown Complier. Please specify including file in the libpluginhelper_assert.cpp"
#endif


LIBPLUGINHELPER_API void libpluginhelper_assert( int expression )
{
    #ifdef _DEBUG
    assert(expression);
    #endif
}
