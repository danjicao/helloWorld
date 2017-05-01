#include <string>
#include "config.h"
#include "libexample.h"
#include "libplugins_events.h"


namespace {
    int init( const char * parameters, PLUGIN_EVENT_HANDLER eventHandler) {
        PLUGIN_UNUSED_PARAMETER(parameters);
        PLUGIN_UNUSED_PARAMETER(eventHandler);
        printf("libexample: init\n");
        return PLUGIN_STATUS_OK;
    }


    void deinit( void ) {
        printf("libexample: deinit\n");
    }


    int request( const char * parameters, PLUGIN_RESPONSE_HANDLER responseHandler ) {
        PLUGIN_UNUSED_PARAMETER(parameters);
        PLUGIN_UNUSED_PARAMETER(responseHandler);
        return PLUGIN_STATUS_ERROR_UNINIT;
    }


    int request_wait_response( const char * parameters, char ** response ) {
        PLUGIN_UNUSED_PARAMETER(parameters);
        PLUGIN_UNUSED_PARAMETER(response);
        return PLUGIN_STATUS_ERROR_UNINIT;
    }


    int request_without_response( const char * parameters ) {
        PLUGIN_UNUSED_PARAMETER(parameters);
        return PLUGIN_STATUS_ERROR_UNINIT;
    }

    int free_response( char ** response ) {
        if ( !response ) {
            return PLUGIN_STATUS_ERROR_UNKNOWN;
        }

        if ( *response ) {
            delete *response;
            *response = NULL;
        }
        return PLUGIN_STATUS_OK;
    }
}   // end of namespace {


PLUGIN_INFO_APIS_DEFINITION(LIBEXAMPLE_API, libexample, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_VERSION_MAJOR, PROJECT_BUILD_TIME)
PLUGIN_INIT_APIS_DEFINITION(LIBEXAMPLE_API, libexample, ::init, ::deinit)
PLUGIN_REQUEST_APIS_DEFINITION(LIBEXAMPLE_API, libexample, ::request, ::request_wait_response, ::request_without_response, ::free_response)

