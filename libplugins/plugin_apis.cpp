#include "plugin_apis.h"
#include "libplugins_types.h"
#include <boost/dll/shared_library.hpp>
#include <boost/dll/library_info.hpp>
#include <boost/filesystem.hpp>
namespace filesystem = boost::filesystem;


PluginApis::PluginApis( const std::string & path )
    : pluginPath(path)
    , pluginName(PLUGIN_UNKNOWN) {
    filesystem::path libPath(pluginPath);
    boost::system::error_code  errorCodeOfLoadSharedLibrary;
    try {
        pluginName = libPath.stem().string();
        
        pluginLib.reset(new boost::dll::shared_library(libPath, boost::dll::load_mode::rtld_lazy, errorCodeOfLoadSharedLibrary));
        if ( errorCodeOfLoadSharedLibrary.value() ) {
            printf("boost::dll::shared_library %s\n", errorCodeOfLoadSharedLibrary.message().c_str());
        }

        pluginInfo.reset(new boost::dll::library_info(libPath));
        
    }
    catch(...) {
        printf("Error! Failed to call %s, %d, %s (errorCodeOfLoadSharedLibrary: %s)\n", __FUNCTION__, __LINE__, __FILE__, errorCodeOfLoadSharedLibrary.message().c_str());
    }
}


PluginApis::~PluginApis() {
}


std::string PluginApis::getPluginName( void ) const {
    return pluginName;
}


std::string PluginApis::getPluginPath( void ) const {
    return pluginPath;
}


std::vector<std::string> PluginApis::getSymbols( void ) const {
    return pluginInfo?pluginInfo->symbols():std::vector<std::string>();
}


std::vector<std::string> PluginApis::getSymbols( const char * section_name ) const {
    return pluginInfo?pluginInfo->symbols(section_name):std::vector<std::string>();
}


std::vector<std::string> PluginApis::getSymbols( const std::string & section_name ) const {
    return pluginInfo?pluginInfo->symbols(section_name):std::vector<std::string>();
}


std::vector<std::string> PluginApis::getSections( void ) const {
    return pluginInfo?pluginInfo->sections():std::vector<std::string>();
}


bool PluginApis::loadSymbols( void ) {
    return pluginLib && pluginLib->is_loaded();
}


std::string PluginApis::transferFunctionName( const std::string & funcName) {
    std::string syntheticName(pluginName);
    syntheticName.append("_");
    syntheticName.append(funcName);
    return syntheticName;
}


bool PluginApis::has( const std::string & name ) {
    if (  pluginLib
        && pluginLib->is_loaded()
        && pluginLib->has(transferFunctionName(name)) 
        ) {
        return true;
    }
    return false;
}

