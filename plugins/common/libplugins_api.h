#ifndef libplugins_api_h_
#define libplugins_api_h_


#include "libplugins_types.h"


#define PLUGIN_INFO_APIS_DECLARATION( apiPrefix, pluginName ) \
    apiPrefix const char * pluginName##_get_plugin_version( void ); \
    apiPrefix const char * pluginName##_get_plugin_revision( void ); \
    apiPrefix const char * pluginName##_get_plugin_soversion( void ); \
    apiPrefix const char * pluginName##_get_plugin_name( void ); \
    apiPrefix const char * pluginName##_get_plugin_type( void ); \
    apiPrefix const char * pluginName##_get_plugin_buildtime( void );


#define PLUGIN_INFO_APIS_DEFINITION( apiPrefix, pluginName, pluginVersion, pluginRevision, pluginSoVersion, pluginBuildTime ) \
    apiPrefix const char * pluginName##_get_plugin_version( void ) { \
        return pluginVersion; \
    } \
    apiPrefix const char * pluginName##_get_plugin_revision( void ) { \
        return pluginRevision; \
    } \
    apiPrefix const char * pluginName##_get_plugin_soversion( void ) { \
        return pluginSoVersion; \
    } \
    apiPrefix const char * pluginName##_get_plugin_name( void ) { \
        return #pluginName; \
    } \
    apiPrefix const char * pluginName##_get_plugin_type( void ) { \
        return PLUGIN_TYPE; \
    } \
    apiPrefix const char * pluginName##_get_plugin_buildtime( void ) { \
        return pluginBuildTime; \
    }


#define PLUGIN_INIT_APIS_DECLARATION( apiPrefix, pluginName ) \
    apiPrefix int  pluginName##_init( const char *, PLUGIN_EVENT_HANDLER ); \
    apiPrefix void pluginName##_deinit( void );


#define PLUGIN_INIT_APIS_DEFINITION( apiPrefix, pluginName, initFunc, deinitFunc ) \
    apiPrefix int  pluginName##_init( const char * parameters, PLUGIN_EVENT_HANDLER eventHandler ) { \
        return initFunc( parameters, eventHandler ); \
    } \
    apiPrefix void pluginName##_deinit( void ) { \
        deinitFunc(); \
    }


#define PLUGIN_REQUEST_APIS_DECLARATION( apiPrefix, pluginName ) \
    apiPrefix int  pluginName##_request( const char *, PLUGIN_RESPONSE_HANDLER ); \
    apiPrefix int  pluginName##_request_wait_response( const char *, char ** ); \
    apiPrefix int  pluginName##_request_without_response( const char * ); \
    apiPrefix int  pluginName##_free_response( char ** response );


#define PLUGIN_REQUEST_APIS_DEFINITION( apiPrefix, pluginName, requestFunc, requestWaitResponseFunc, requestWithoutResponseFunc, freeResponseFunc ) \
    apiPrefix int  pluginName##_request( const char * parameters, PLUGIN_RESPONSE_HANDLER responseHandler ) { \
        return requestFunc( parameters, responseHandler ); \
    } \
    apiPrefix int  pluginName##_request_wait_response( const char * parameters, char ** response ) { \
        return requestWaitResponseFunc( parameters, response ); \
    } \
    apiPrefix int  pluginName##_request_without_response( const char * parameters ) { \
        return requestWithoutResponseFunc( parameters ); \
    } \
    apiPrefix int  pluginName##_free_response( char ** response ) { \
        return freeResponseFunc( response ); \
    } 


#define PLUGIN_APIS_DECLARATION( apiPrefix, pluginName ) \
    PLUGIN_INFO_APIS_DECLARATION( apiPrefix, pluginName ) \
    PLUGIN_INIT_APIS_DECLARATION( apiPrefix, pluginName ) \
    PLUGIN_REQUEST_APIS_DECLARATION( apiPrefix, pluginName )


#endif  // end of #ifndef libplugins_api_h_

