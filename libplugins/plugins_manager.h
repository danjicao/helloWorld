#ifndef plugins_manager_h_
#define plugins_manager_h_


#include <deque>
#include <boost/filesystem.hpp>
#include "libplugins_types.h"
#include "plugin_apis_v1.h"



class CPluginsManager {
public:
    CPluginsManager(const char * _parameters, PLUGIN_EVENT_HANDLER _eventHandler, const boost::filesystem::path & _modulesDirectory);
    virtual ~CPluginsManager();

    virtual int doEvent( const char * );
    virtual int doTask( const char * );
    PLUGIN_EVENT_HANDLER getEventHandler( void );


protected:
    virtual bool loadPlugins();


private:
    std::string parameters;
    PLUGIN_EVENT_HANDLER eventHandler;
    std::vector<boost::filesystem::path> modulesDirectories;
    
    typedef PluginApisV1 PLUGIN_APIS;
    typedef std::deque<PLUGIN_APIS *> PLUGIN_CONTAINER_t;
    PLUGIN_CONTAINER_t pluginsContainer;


    static bool loadPluginsFrom( const boost::filesystem::path & _modulesDirectory, PLUGIN_CONTAINER_t & _pluginsContainer, const std::string & parameters, PLUGIN_EVENT_HANDLER eventHandler );
    static void clearPluginsContainer( PLUGIN_CONTAINER_t & _pluginsContainer );

};  // end of class CPluginsManager
#endif  // end if #ifndef plugins_manager_h_

