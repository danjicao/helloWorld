#include "plugins_manager.h"
#include "config.h"


CPluginsManager::CPluginsManager(const char * _parameters, PLUGIN_EVENT_HANDLER _eventHandler, const boost::filesystem::path & _modulesDirectory)
    : parameters(_parameters)
    , eventHandler(_eventHandler) {
    
    boost::filesystem::path initDirectory = boost::filesystem::initial_path();
    initDirectory.append("/");
    initDirectory.append(PLUGIN_MODULES_DIRNAME);
    modulesDirectories.push_back(initDirectory);
    modulesDirectories.push_back(_modulesDirectory);

    loadPlugins();
}


CPluginsManager::~CPluginsManager() {
    clearPluginsContainer(pluginsContainer);
}


bool CPluginsManager::loadPlugins() {
    bool result = false;
    PLUGIN_CONTAINER_t tempPluginsContainer;

    for ( std::vector<boost::filesystem::path>::const_iterator dir = modulesDirectories.cbegin(); dir != modulesDirectories.cend(); ++ dir ) {
        if ( CPluginsManager::loadPluginsFrom(*dir, tempPluginsContainer, parameters, eventHandler) ) {
            result = true;
        }
    }

    if ( result ) {
        pluginsContainer.swap(tempPluginsContainer);
        clearPluginsContainer(tempPluginsContainer);
    }

    return result;
}


bool CPluginsManager::loadPluginsFrom( const boost::filesystem::path & _modulesDirectory, PLUGIN_CONTAINER_t & _pluginsContainer, const std::string & parameters, PLUGIN_EVENT_HANDLER eventHandler ) {
    printf("loadPluginsFrom: try %s\n", _modulesDirectory.c_str());
    if ( !boost::filesystem::exists( _modulesDirectory ) ) {
        return false;
    }

    boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end
    for ( boost::filesystem::directory_iterator file(_modulesDirectory); file != end_itr; ++file ) {
        if ( is_regular_file(file->path()) ) {
            PLUGIN_APIS * plugin = new PLUGIN_APIS( file->path().string() );
            if( plugin->loadSymbols() ) {
                printf("Load plugin: %s\n", file->path().string().c_str());
                printf("    get_plugin_version   :%s\n", plugin->get_plugin_version());
                printf("    get_plugin_revision  :%s\n", plugin->get_plugin_revision());
                printf("    get_plugin_soversion :%s\n", plugin->get_plugin_soversion());
                printf("    get_plugin_name      :%s\n", plugin->get_plugin_name());
                printf("    get_plugin_type      :%s\n", plugin->get_plugin_type());
                printf("    get_plugin_buildtime :%s\n", plugin->get_plugin_buildtime());

                if ( 0 != strcmp(plugin->get_plugin_type(), PLUGIN_TYPE) ) {
                    printf("Error! Failed to load plugin: %s\n", file->path().string().c_str());
                }
                else if ( 0 == strcmp(plugin->get_plugin_name(), PROJECT) ) {
                    printf("Error! Failed to load plugin: %s\n", file->path().string().c_str());
                }
                else if ( 0 != strcmp(plugin->getPluginName().c_str(), plugin->get_plugin_name()) ) {
                    printf("Error! Failed to load plugin: %s\n", file->path().string().c_str());
                }
                else {
                    plugin->init(parameters.c_str(), eventHandler);
                    _pluginsContainer.push_back(plugin);
                    plugin = NULL;
                }
            }
            else {
                printf("Error! Failed to load plugin: %s\n", file->path().string().c_str());
            }
            delete plugin;
        }
        else
        {
            printf("UnLoad plugin: %s\n", file->path().string().c_str());
        }
    }

    return true;
}


void CPluginsManager::clearPluginsContainer( PLUGIN_CONTAINER_t & _pluginsContainer ) {
    while( !_pluginsContainer.empty() ) {
        PLUGIN_APIS * plugin = _pluginsContainer.front();
        _pluginsContainer.pop_front();

        if ( plugin ) {
            try {
                plugin->deinit();
                delete plugin;
            }
            catch(...) {
                printf("Error! Failed to call %s, %d, %s\n", __FUNCTION__, __LINE__, __FILE__);
            }
        }
    }
}


int CPluginsManager::doEvent( const char * event) {
    if ( eventHandler ) {
        return eventHandler(event);
    }

    return 0;
}


int CPluginsManager::doTask( const char * ) {
    return 0;
}


PLUGIN_EVENT_HANDLER CPluginsManager::getEventHandler( void ) {
    return eventHandler;
}

