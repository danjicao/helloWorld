#include "plugin_apis_v1.h"
#include "libplugins_events.h"
#include <boost/dll/shared_library.hpp>


PluginApisV1::PluginApisV1( const std::string & path )
    : PluginApis(path) {
}


PluginApisV1::~PluginApisV1() {
}


bool PluginApisV1::loadSymbols( void ) {
    bool loadParentSymbols = PluginApis::loadSymbols();
    if (!loadParentSymbols) {
        printf("Error! Failed to call %s, %d, %s\n", __FUNCTION__, __LINE__, __FILE__);
        return false;
    }

    const std::string funcNames[] = {
        PLUGIN_GET_PLUGIN_VERSION_FUNCNAME,
        PLUGIN_GET_PLUGIN_REVISION_FUNCNAME,
        PLUGIN_GET_PLUGIN_SOVERSION_FUNCNAME,
        PLUGIN_GET_PLUGIN_NAME_FUNCNAME,
        PLUGIN_GET_PLUGIN_TYPE_FUNCNAME,
        PLUGIN_GET_PLUGIN_BUILDTIME_FUNCNAME,
        PLUGIN_INIT_FUNCNAME,
        PLUGIN_DEINIT_FUNCNAME,
        PLUGIN_REQUEST_FUNCNAME,
        PLUGIN_REQUEST_WAIT_RESPONSE_FUNCNAME,
        PLUGIN_REQUEST_WITHOUT_RESPONSE_FUNCNAME,
        PLUGIN_FREE_RESPONSE_FUNCNAME,
    };

    const size_t funcNamesCount = sizeof(funcNames) / sizeof(*funcNames);

    for ( size_t i = 0; i < funcNamesCount; ++i ) {
        if ( !has(funcNames[i]) ) {
            printf("XXX %s\n", funcNames[i].c_str());
            return false;
        }
    }

    return true;
}


const char * PluginApisV1::get_plugin_version( void ) const {
    try{
        PLUGIN_GET_PLUGIN_VERSION & func = pluginLib->get<PLUGIN_GET_PLUGIN_VERSION>(transferFunctionName(PLUGIN_GET_PLUGIN_VERSION_FUNCNAME));
        return func();
    }
    catch(...) {
    }
    return PLUGIN_UNKNOWN;
}


const char * PluginApisV1::get_plugin_revision( void ) const {
    try{
        PLUGIN_GET_PLUGIN_REVISION & func = pluginLib->get<PLUGIN_GET_PLUGIN_REVISION>(transferFunctionName(PLUGIN_GET_PLUGIN_REVISION_FUNCNAME));
        return func();
    }
    catch(...) {
    }
    return PLUGIN_UNKNOWN;
}


const char * PluginApisV1::get_plugin_soversion( void ) const {
    try{
        PLUGIN_GET_PLUGIN_SOVERSION & func = pluginLib->get<PLUGIN_GET_PLUGIN_SOVERSION>(transferFunctionName(PLUGIN_GET_PLUGIN_SOVERSION_FUNCNAME));
        return func();
    }
    catch(...) {
    }
    return PLUGIN_UNKNOWN;
}


const char * PluginApisV1::get_plugin_name( void ) const {
    try{
        PLUGIN_GET_PLUGIN_NAME & func = pluginLib->get<PLUGIN_GET_PLUGIN_NAME>(transferFunctionName(PLUGIN_GET_PLUGIN_NAME_FUNCNAME));
        return func();
    }
    catch(...) {
    }
    return PLUGIN_UNKNOWN;
}


const char * PluginApisV1::get_plugin_type( void ) const {
    try{
        PLUGIN_GET_PLUGIN_TYPE & func = pluginLib->get<PLUGIN_GET_PLUGIN_TYPE>(transferFunctionName(PLUGIN_GET_PLUGIN_TYPE_FUNCNAME));
        return func();
    }
    catch(...) {
    }
    return PLUGIN_UNKNOWN;
}


const char * PluginApisV1::get_plugin_buildtime( void ) const {
    try{
        PLUGIN_GET_PLUGIN_BUILDTIME & func = pluginLib->get<PLUGIN_GET_PLUGIN_BUILDTIME>(transferFunctionName(PLUGIN_GET_PLUGIN_BUILDTIME_FUNCNAME));
        return func();
    }
    catch(...) {
    }
    return PLUGIN_UNKNOWN;
}


int  PluginApisV1::init( const char * parameters, PLUGIN_EVENT_HANDLER eventHandler ) {
    try{
        PLUGIN_INIT & func = pluginLib->get<PLUGIN_INIT>(transferFunctionName(PLUGIN_INIT_FUNCNAME));
        return func(parameters, eventHandler);
    }
    catch(...) {
    }
    return PLUGIN_STATUS_ERROR_UNKNOWN;
}


void PluginApisV1::deinit( void ) {
    try{
        PLUGIN_DEINIT & func = pluginLib->get<PLUGIN_DEINIT>(transferFunctionName(PLUGIN_DEINIT_FUNCNAME));
        func();
    }
    catch(...) {
    }
}


int  PluginApisV1::request( const char * parameters, PLUGIN_RESPONSE_HANDLER responseHandler) {
    try{
        PLUGIN_REQUEST & func = pluginLib->get<PLUGIN_REQUEST>(transferFunctionName(PLUGIN_REQUEST_FUNCNAME));
        return func(parameters, responseHandler);
    }
    catch(...) {
    }
    return PLUGIN_STATUS_ERROR_UNKNOWN;
}


int  PluginApisV1::request_wait_response( const char * parameters, char ** response ) {
    try{
        PLUGIN_REQUEST_WAIT_RESPONSE & func = pluginLib->get<PLUGIN_REQUEST_WAIT_RESPONSE>(transferFunctionName(PLUGIN_REQUEST_WAIT_RESPONSE_FUNCNAME));
        return func(parameters, response);
    }
    catch(...) {
    }
    return PLUGIN_STATUS_ERROR_UNKNOWN;
}


int  PluginApisV1::request_without_response( const char * parameters ) {
    try{
        PLUGIN_REQUEST_WITHOUT_RESPONSE & func = pluginLib->get<PLUGIN_REQUEST_WITHOUT_RESPONSE>(transferFunctionName(PLUGIN_REQUEST_WITHOUT_RESPONSE_FUNCNAME));
        return func(parameters);
    }
    catch(...) {
    }
    return PLUGIN_STATUS_ERROR_UNKNOWN;
}


int  PluginApisV1::free_response( char ** response ) {
    try{
        PLUGIN_FREE_RESPONSE & func = pluginLib->get<PLUGIN_FREE_RESPONSE>(transferFunctionName(PLUGIN_FREE_RESPONSE_FUNCNAME));
        return func(response);
    }
    catch(...) {
    }
    return PLUGIN_STATUS_ERROR_UNKNOWN;
}


bool PluginApisV1::isEqual(const PluginApisV1 * rhs ) const {
    if ( 0 == strcmp( get_plugin_name(), rhs->get_plugin_name() )
       && 0 == strcmp( get_plugin_soversion(), rhs->get_plugin_soversion() )
       && 0 == strcmp( get_plugin_version(), rhs->get_plugin_version() )
       ) {
        return true;
    }
    return false;
}
