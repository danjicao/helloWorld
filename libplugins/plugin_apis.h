#ifndef plugin_apis_h_
#define plugin_apis_h_


#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>


namespace boost {
    namespace dll {
        class shared_library;
        class library_info;
    }   // end of namespace dll {
}   // end of namespace boost {


class PluginApis{
public:
    PluginApis( const std::string & path );
    virtual ~PluginApis();

    std::string getPluginName( void ) const;
    std::string getPluginPath( void ) const;
    virtual bool loadSymbols( void );
    
    std::vector<std::string> getSymbols( void ) const;
    std::vector<std::string> getSymbols( const char * section_name ) const;
    std::vector<std::string> getSymbols( const std::string & section_name ) const;
    std::vector<std::string> getSections( void ) const;


protected:
    boost::shared_ptr<boost::dll::shared_library> pluginLib;
    boost::shared_ptr<boost::dll::library_info> pluginInfo;
    std::string transferFunctionName( const std::string & funcName) const;
    bool has( const std::string & name );


private:
    const std::string pluginPath;
    std::string pluginName;
};  // end of class PluginApis{


#endif  // end of #ifndef plugin_apis_h_

