#ifndef libplugins_types_h_
#define libplugins_types_h_


#define PLUGIN_TYPE "A8B37229-C90C-51E3-82FF-3774245E4948"
#define PLUGIN_UNKNOWN "unknown"
#define PLUGIN_MODULES_DIRNAME "modules"


#define PLUGIN_UNUSED_PARAMETER(x) (void)(x)


typedef int  (* PLUGIN_EVENT_HANDLER)( const char * );
typedef int  (* PLUGIN_RESPONSE_HANDLER)( const char * );


#define PLUGIN_GET_PLUGIN_VERSION_FUNCNAME "get_plugin_version"
typedef const char * (PLUGIN_GET_PLUGIN_VERSION)( void );
#define PLUGIN_GET_PLUGIN_REVISION_FUNCNAME "get_plugin_revision"
typedef const char * (PLUGIN_GET_PLUGIN_REVISION)( void );
#define PLUGIN_GET_PLUGIN_SOVERSION_FUNCNAME "get_plugin_soversion"
typedef const char * (PLUGIN_GET_PLUGIN_SOVERSION)( void );
#define PLUGIN_GET_PLUGIN_NAME_FUNCNAME "get_plugin_name"
typedef const char * (PLUGIN_GET_PLUGIN_NAME)( void );
#define PLUGIN_GET_PLUGIN_TYPE_FUNCNAME "get_plugin_type"
typedef const char * (PLUGIN_GET_PLUGIN_TYPE)( void );
#define PLUGIN_GET_PLUGIN_BUILDTIME_FUNCNAME "get_plugin_buildtime"
typedef const char * (PLUGIN_GET_PLUGIN_BUILDTIME)( void );

#define PLUGIN_INIT_FUNCNAME "init"
typedef int  (PLUGIN_INIT)( const char *, PLUGIN_EVENT_HANDLER );
#define PLUGIN_DEINIT_FUNCNAME "deinit"
typedef void (PLUGIN_DEINIT)( void );

#define PLUGIN_REQUEST_FUNCNAME "request"
typedef int  (PLUGIN_REQUEST)( const char *, PLUGIN_RESPONSE_HANDLER );
#define PLUGIN_REQUEST_WAIT_RESPONSE_FUNCNAME "request_wait_response"
typedef int  (PLUGIN_REQUEST_WAIT_RESPONSE)( const char *, char ** );
#define PLUGIN_REQUEST_WITHOUT_RESPONSE_FUNCNAME "request_without_response"
typedef int  (PLUGIN_REQUEST_WITHOUT_RESPONSE)( const char * );
#define PLUGIN_FREE_RESPONSE_FUNCNAME "free_response"
typedef int  (PLUGIN_FREE_RESPONSE)( char ** );

#endif  // end of #ifndef libplugins_types_h_

