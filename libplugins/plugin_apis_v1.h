#ifndef plugin_apis_v1_h_
#define plugin_apis_v1_h_


#include "plugin_apis.h"
#include "libplugins_types.h"


class PluginApisV1: public PluginApis {
public:
    PluginApisV1( const std::string & path );
    virtual ~PluginApisV1();

    virtual bool loadSymbols( void );

    const char * get_plugin_version( void );
    const char * get_plugin_revision( void );
    const char * get_plugin_soversion( void );
    const char * get_plugin_name( void );
    const char * get_plugin_type( void );
    const char * get_plugin_buildtime( void );
    int  init( const char *, PLUGIN_EVENT_HANDLER );
    void deinit( void );
    int  request( const char *, PLUGIN_RESPONSE_HANDLER );
    int  request_wait_response( const char *, char ** );
    int  request_without_response( const char * );
    int  free_response( char ** );

};  // end of class PluginApisV1


#endif  // end of #ifndef plugin_apis_v1_h_
