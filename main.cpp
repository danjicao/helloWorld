#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "config.h"
#include "libhello/libhello.h"
#include "libsysinfo/libsysinfo.h"
#include "infocollector.h"

#ifdef ENABLE_PLUGINS
#include "libplugins/libplugins.h"
#endif

#ifdef ENABLE_LIBPOCO
    #include <Poco/UUIDGenerator.h>
    using namespace Poco;
#else
    #include <uuid/uuid.h>
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
}


#ifdef ENABLE_PLUGINS
int PluginEventHandler( const char * ) {

    return 0;
}
#endif

namespace {


CInfoCollector g_info(false);


typedef size_t (* FP_ConvertFunc)( std::istream & input, std::ostream & output, const CInfoCollector & info );


size_t convertHex2Bin( std::istream & input, std::ostream & output, const CInfoCollector & info ) {
    bool result = true;
    const char digits[] = "0123456789abcdef";
    size_t index = 0;
    char u,v;
    unsigned char numU = 0, numV = 0;

    while ( ! input.eof() ) {
        u = input.get();
        input.peek();
        if ( 0x0A == u || 0x0D == u ) {
            continue;
        }
        ++index;

        const char * pu = strchr(digits, tolower(u));
        if ( pu ) {
            numU = pu-digits;
            info.debug("u[%2zu]=%d", index, numU);
        }
        else {
            result = false;
            info.error("Error! Conversion failed at %zu (0x%02X).", index, u);
            break;
        }

        if ( input ) {
            v = input.get();
            input.peek();
            if ( 0x0A == u || 0x0D == u ) {
                v = '0';
            }
            ++index;
        }
        else {
            v = '0';
        }

        const char * pv = strchr(digits, tolower(v));
        if ( pv ) {
            numV = pv-digits;
            info.debug("v[%2zu]=%d", index, numV);
        }
        else {
            result = false;
            info.error("Error! Conversion failed at %zu (0x%02X).", index, v);
            break;
        }

        unsigned char num = numU << 4 | numV;
        info.debug("u x 16 + v = %d = 0x%02X", num, num);

        if ( output ) {
            output << (unsigned char) num;
        }
    }

    return result?index:0;
}


size_t convertBin2Hex( std::istream & input, std::ostream & output, const CInfoCollector & info ) {
    const size_t colCount = 16;
    size_t row = 0;
    size_t col = 0;
    size_t index = 0;
    char c;

    while ( ! input.eof() ) {
        if ( 0 == col ) {
            output << "[" << std::setfill(' ') << std::setw(10) << std::dec << row << "]";
        }

        c = input.get();
        output << " " << std::setfill('0') << std::setw(2) << std::hex << std::uppercase << static_cast<unsigned int>(c);
        input.peek();
        ++index;
        ++col;

        if ( colCount == col ) {
            output << std::endl;
            col = 0;
            ++row;
        }
    }

    output << std::endl;
    info.debug("total size=%zu", index);
    return index;
}


size_t generateUUID( std::istream & input, std::ostream & output, const CInfoCollector & info ) {
    std::string result;

    #ifdef ENABLE_LIBPOCO
    UUIDGenerator uuidGenerator;
    UUID uuid = uuidGenerator.createRandom();
    result = uuid.toString();
    #else
    char uuid_str[37] = {'\0'};
    uuid_t uuid;
    uuid_generate_random(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    result.assign(uuid_str);
    #endif

    if ( ! result.empty() ) {
        output << result.c_str() << std::endl;
    }
    return result.size();
}


}    // end of namespace {


int CCALL main ( int argc, /*const*/ char * argv[], /*const*/ char* /*const*/ * envp )
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("hello", po::value<std::string>()->implicit_value("World"), "print hello message")
        ("version", "show version")
        ("all,a", "run all sections")
        ("arguments", "show arguments")
        ("env", "show environment variables")
    #ifdef ENABLE_PLUGINS
        ("plugins,p", "enable plugins system")
    #endif
        ("printCompliedInfo", "print complied information")
        ("verbose,v", po::value<int>()->implicit_value(1), "verbosity level")
        ("conversion-mode,c", po::value<std::string>()->default_value("")->implicit_value("hex2bin"), "convert hex string to bin")
        ("input,i" , po::value<std::string>()->default_value("")->implicit_value(""), "input")
        ("output,o", po::value<std::string>()->default_value("")->implicit_value(""), "output")
    ;


    std::string conversionMode;
    std::string input;
    std::string output;
    std::string helloTo;
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if ( vm.count("help") ) {
            g_info.options(desc);
            return 1;
        }

        bool runAllSections( vm.count("all") > 0 );
        if ( runAllSections ) {
            g_info.system("--all");
        }

        if ( runAllSections || vm.count("version") ) {
            g_info.system(">> version:");
            g_info.system("%s ver. %s, rev. %s (%s)", PROJECT, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_BUILD_TIME);
            g_info.system("%-10s ver. %s, rev. %s, sover. %s (%s)", libsysinfo_get_plugin_name(), libsysinfo_get_plugin_version(), libsysinfo_get_plugin_revision(), libsysinfo_get_plugin_soversion(), libsysinfo_get_plugin_buildtime());
            g_info.system("%-10s ver. %s, rev. %s, sover. %s (%s)", libhello_get_plugin_name(), libhello_get_plugin_version(), libhello_get_plugin_revision(), libhello_get_plugin_soversion(), libhello_get_plugin_buildtime());

            #ifdef ENABLE_PLUGINS
            g_info.system("%-10s ver. %s, rev. %s, sover. %s (%s)", libplugins_get_plugin_name(), libplugins_get_plugin_version(), libplugins_get_plugin_revision(), libplugins_get_plugin_soversion(), libplugins_get_plugin_buildtime());
            #endif
        }

        if ( runAllSections || vm.count("arguments") ) {
            g_info.system(">>  arguments:");
            g_info.system("    argc=%d", argc);
            for( int i = 0; i < argc; ++i )
            {
                g_info.system( "    argv[%2d] = \"%s\"", i, argv[i] );
            }
        }

        if ( runAllSections || vm.count("env") ) {
            g_info.system(">>  environment variables:");
            for (const char* const* env = envp; *env != NULL; ++env)
            {
                g_info.system("    %s", *env);
            }
        }

        #ifdef ENABLE_PLUGINS
        if ( runAllSections || vm.count("plugins") ) {
            g_info.system("--plugins");
            libplugins_init("{}", PluginEventHandler);
            libplugins_deinit();
        }
        #endif

        if ( runAllSections || vm.count("printCompliedInfo") ) {
            libsysinfo_printCompliedInfo();
            libsysinfo_printByteOrderType();
            g_info.system("libsysinfo_isCharSigned=%d", libsysinfo_isCharSigned());
        }

        if ( runAllSections || vm.count("hello") ) {
            helloTo = vm["hello"].as<std::string>();
        }

        if ( vm.count("verbose") ) {
            bool verbose = vm["verbose"].as<int>() != 0;
            g_info.system("--verbose=%d", verbose?1:0);
            g_info.setVerbose(verbose);
        }


        if ( vm.count("conversion-mode") ) {
            conversionMode = vm["conversion-mode"].as<std::string>();
            if ( !conversionMode.empty() ) {
                if ( '=' == conversionMode[0] ) {
                    conversionMode.erase(0, 1);
                }

                g_info.system("--conversion-mode=%s", conversionMode.c_str());
            }
        }


        if ( vm.count("input") ) {
            input = vm["input"].as<std::string>();

            if ( !input.empty() ) {
                if ( '=' == input[0] ) {
                    input.erase(0, 1);
                }
                g_info.system("--input=%s", input.c_str());
            }
        }


        if ( vm.count("output") ) {
            output = vm["output"].as<std::string>();

            if ( !output.empty() ) {
                g_info.system("--output=%s", output.c_str());
            }
        }


        g_info.system(">>  Appliction Begin");


        if ( !helloTo.empty() ) {
            libhello_helloTo(helloTo.c_str());
            //libhello_HiddenMe(); // Hence, HiddenMe should NOT be called.
        }


        if ( !conversionMode.empty() ) {
            bool result = false;
            FP_ConvertFunc convertFunc = NULL;
            if( 0 == strcmp(conversionMode.c_str(), "hex2bin") ) {
                convertFunc = convertHex2Bin;
            }
            else if( 0 == strcmp(conversionMode.c_str(), "bin2hex") ) {
                convertFunc = convertBin2Hex;
            }
            else if( 0 == strcmp(conversionMode.c_str(), "uuid") ) {
                convertFunc = generateUUID;
            }
            else {
                g_info.error("Error! There is invalid parameter '--conversion-mode=%s'.", conversionMode.c_str());
            }

            if ( convertFunc ) {
                std::streambuf * pOutputBuf = NULL;
                std::ofstream ofs;
                std::istream * pInputStream = NULL;
                std::ifstream ifs;

                do{
                    if ( output.empty() ) {
                        pOutputBuf = std::cout.rdbuf();
                    }
                    else {
                        ofs.open(output.c_str(), std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
                        if ( ofs.is_open() ) {
                            pOutputBuf = ofs.rdbuf();
                        }
                        else {
                            g_info.error("Error! There is invalid parameter '--output' (file can't open).");
                            break;
                        }
                    }

                    if ( input.empty() || "-" == input ) {
                        pInputStream = & std::cin;
                    }
                    else {
                        ifs.open( input.c_str(), std::ios_base::in );
                        if ( ifs.is_open() ) {
                            pInputStream = &ifs;
                        }
                        else {
                            g_info.error("Error! There is invalid parameter '--input' (file can't open).");
                            break;
                        }
                    }

                    std::ostream outstream(pOutputBuf);
                    size_t convertedSize = convertFunc(*pInputStream, outstream, g_info);
                    if ( 0 < convertedSize ) {
                        result = true;
                    }
                } while (0);

                if ( ifs.is_open() ) {
                    ifs.close();
                }

                if ( ofs.is_open() ) {
                    ofs.close();
                }
            }

            if ( result ) {
                g_info.trace("Conversion OK!");
            }
        }


        DoSomethingInMainBody();


        g_info.system(">>  Appliction Finish");


    } catch ( const po::unknown_option& e ) {
        g_info.error("Error! (boost::program_options) %s", e.what());
        g_info.options(desc);
        return 1;
    } catch ( const po::error& e ) {
        g_info.error("Error! (boost::program_options) %s", e.what());
        return 1;
    } catch ( const std::exception& e ) {
        g_info.error("Error! %s", e.what());
        return 1;
    } catch ( ... ) {
        g_info.error("Error! Unknown.");
        return 1;
    }

    return 0;
}


void beforeMain( void )
{
    g_info.system(">>  Before Main");
}


void afterMain( void )
{
    g_info.system(">>  After Main");
}


