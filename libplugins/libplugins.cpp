#include <boost/dll/runtime_symbol_info.hpp>
#include "libplugins.h"
#include "config.h"
#include "libplugins_events.h"
#include "plugins_manager.h"


namespace {
    CPluginsManager * g_PluginsManager = NULL;
    int init( const char * parameters, PLUGIN_EVENT_HANDLER eventHandler) {
        boost::filesystem::path defaultModulesDirectory = boost::dll::symbol_location_ptr(libplugins_get_plugin_version).parent_path();
        defaultModulesDirectory.append("/");
        defaultModulesDirectory.append(PLUGIN_MODULES_DIRNAME);

        if (!g_PluginsManager) {
            g_PluginsManager = new CPluginsManager(parameters, eventHandler, defaultModulesDirectory);
        }
        return PLUGIN_STATUS_OK;
    }


    void deinit( void ) {
        if (g_PluginsManager) {
            PLUGIN_EVENT_HANDLER eventHandler = g_PluginsManager->getEventHandler();
            delete g_PluginsManager;
            g_PluginsManager = NULL;
            if (eventHandler) {
                // TODO: send event about deinit
            }
        }
        else {
            // TODO: print message to stderr
        }
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


PLUGIN_INFO_APIS_DEFINITION(LIBPLUGINS_API, libplugins, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_VERSION_MAJOR, PROJECT_BUILD_TIME)
PLUGIN_INIT_APIS_DEFINITION(LIBPLUGINS_API, libplugins, ::init, ::deinit)
PLUGIN_REQUEST_APIS_DEFINITION(LIBPLUGINS_API, libplugins, ::request, ::request_wait_response, ::request_without_response, ::free_response)

