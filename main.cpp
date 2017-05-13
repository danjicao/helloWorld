#include <stdio.h>
#include <iostream>
#include "config.h"
#include "libhello/libhello.h"
#include "libsysinfo/libsysinfo.h"

#ifdef ENABLE_PLUGINS
#include "libplugins/libplugins.h"
#endif


#include <boost/program_options.hpp>
namespace po = boost::program_options;


static void beforeMain( void );
static void afterMain( void );


#ifdef _MSC_VER
    #include <stdlib.h>
    #define CCALL __cdecl
    #pragma section(".CRT$XCU",read)

    static void __cdecl AFTER_MAIN( void )
    {
        afterMain();
        system("PAUSE");
    }

    static void __cdecl BEFORE_MAIN( void )
    {
        beforeMain();
        atexit(AFTER_MAIN);
    }

    __declspec(allocate(".CRT$XCU")) void (__cdecl * FP_BEFORE_MAIN)( void ) = BEFORE_MAIN;


#elif defined(__GNUC__)
    #define CCALL
    static __attribute__((destructor)) void AFTER_MAIN( void )
    {
        afterMain();
    }

    static __attribute__((constructor)) void BEFORE_MAIN( void )
    {
        beforeMain();
    }


#else
    #error "Unknown Complier. Please specify incluing file in the main.cpp."
#endif


void DoSomethingInMainBody( void )
{
    libhello_helloTo("World");
    //libhello_HiddenMe(); // Hence, HiddenMe should NOT be called.
}


#ifdef ENABLE_PLUGINS
int PluginEventHandler( const char * ) {

    return 0;
}
#endif


int CCALL main ( int argc, /*const*/ char * argv[], /*const*/ char* /*const*/ * envp )
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("version,v", "show version")
        ("arguments", "show arguments")
        ("env", "show environment variables")
    #ifdef ENABLE_PLUGINS
        ("plugins,p", "enable plugins system")
    #endif
        ("printCompliedInfo", "print complied information")
    ;

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);    

        if ( vm.count("help") ) {
            std::cout << desc << std::endl;
            return 1;
        }
        
        if ( vm.count("version") ) {
            printf("%s ver. %s, rev. %s (%s)\n", PROJECT, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_BUILD_TIME);
            printf("%-10s ver. %s, rev. %s, sover. %s (%s)\n", libsysinfo_get_plugin_name(), libsysinfo_get_plugin_version(), libsysinfo_get_plugin_revision(), libsysinfo_get_plugin_soversion(), libsysinfo_get_plugin_buildtime());
            printf("%-10s ver. %s, rev. %s, sover. %s (%s)\n", libhello_get_plugin_name(), libhello_get_plugin_version(), libhello_get_plugin_revision(), libhello_get_plugin_soversion(), libhello_get_plugin_buildtime());

            #ifdef ENABLE_PLUGINS
            printf("%10s ver. %s, rev. %s, sover. %s (%s)\n", libplugins_get_plugin_name(), libplugins_get_plugin_version(), libplugins_get_plugin_revision(), libplugins_get_plugin_soversion(), libplugins_get_plugin_buildtime());
            #endif
        }

        if ( vm.count("arguments") ) {
            printf(">>  arguments:\n");
            printf("    argc=%d\n", argc);
            for( int i = 0; i < argc; ++i )
            {
                printf( "    argv[%2d] = \"%s\"\n", i, argv[i] );
            }
        }

        if ( vm.count("env") ) {
            printf(">>  environment variables:\n");
            for (const char* const* env = envp; *env != NULL; ++env)
            {
                printf("    %s\n", *env);
            }
        }

        #ifdef ENABLE_PLUGINS
        if ( vm.count("plugins") ) {
            libplugins_init("", PluginEventHandler);
            libplugins_deinit();
        }
        #endif
        
        if ( vm.count("printCompliedInfo") ) {
            libsysinfo_printCompliedInfo();
            libsysinfo_printByteOrderType();
            printf("libsysinfo_isCharSigned=%d\n", libsysinfo_isCharSigned());
        }

        printf(">>  Appliction Begin\n");

        DoSomethingInMainBody();

        printf(">>  Appliction Finish\n");

    } catch ( const po::unknown_option& e ) {
        std::cerr << "Error! (boost::program_options) " << e.what() << std::endl;
        std::cerr << desc << std::endl;
        return 1;
    } catch ( const po::error& e ) {
        std::cerr << "Error! (boost::program_options) " << e.what() << std::endl;
        return 1;
    } catch ( const std::exception& e ) {
        std::cerr << "Error! " << e.what() << std::endl;
        return 1;
    } catch ( ... ) {
        std::cerr << "Error! Unknown." << std::endl;
        return 1;
    }

    return 0;
}


void beforeMain( void )
{
    printf(">>  Before Main\n");
}


void afterMain( void )
{
    printf(">>  After Main\n");
}


