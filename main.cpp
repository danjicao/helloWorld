#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
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


typedef size_t (* FP_ConvertFunc)( std::istream & input, std::ostream & output, bool verbose );


size_t convertHex2Bin( std::istream & input, std::ostream & output, bool verbose ) {
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
            if ( verbose ) {
                printf("u[%2zu]=%d\n", index, numU);
            }
        }
        else {
            result = false;
            printf("Error! Conversion failed at %zu (0x%02X).\n", index, u);
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
            if ( verbose ) {
                printf("v[%2zu]=%d\n", index, numV);
            }
        }
        else {
            result = false;
            printf("Error! Conversion failed at %zu (0x%02X).\n", index, v);
            break;
        }

        unsigned char num = numU << 4 | numV;
        if ( verbose ) {
            printf("u x 16 + v = %d = 0x%02X\n", num, num);
        }

        if ( output ) {
            output << (unsigned char) num;
        }
    }

    return result?index:0;
}


size_t convertBin2Hex( std::istream & input, std::ostream & output, bool verbose ) {
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
            //printf("\n");
            output << std::endl;
            col = 0;
            ++row;
        }
    }

    output << std::endl;
    if ( verbose ) {
        printf("total size=%zu\n", index);
    }
    return index;
}


int CCALL main ( int argc, /*const*/ char * argv[], /*const*/ char* /*const*/ * envp )
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("version,v", "show version")
        ("all,a", "run all sections")
        ("arguments", "show arguments")
        ("env", "show environment variables")
    #ifdef ENABLE_PLUGINS
        ("plugins,p", "enable plugins system")
    #endif
        ("printCompliedInfo", "print complied information")
        ("verbose", po::value<int>()->default_value(0)->implicit_value(1), "verbosity level")
        ("conversion-mode,c", po::value<std::string>()->default_value("hex2bin")->implicit_value("hex2bin"), "convert hex string to bin")
        ("input,i" , po::value<std::string>()->default_value("")->implicit_value(""), "input")
        ("output,o", po::value<std::string>()->default_value("")->implicit_value(""), "output")
    ;

    bool verbose = false;
    std::string conversionMode;
    std::string input;
    std::string output;
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if ( vm.count("help") ) {
            std::cout << desc << std::endl;
            return 1;
        }

        bool runAllSections( vm.count("all") > 0 );

        if ( runAllSections || vm.count("version") ) {
            printf("%s ver. %s, rev. %s (%s)\n", PROJECT, PROJECT_VERSION, PROJECT_GIT_REVISION, PROJECT_BUILD_TIME);
            printf("%-10s ver. %s, rev. %s, sover. %s (%s)\n", libsysinfo_get_plugin_name(), libsysinfo_get_plugin_version(), libsysinfo_get_plugin_revision(), libsysinfo_get_plugin_soversion(), libsysinfo_get_plugin_buildtime());
            printf("%-10s ver. %s, rev. %s, sover. %s (%s)\n", libhello_get_plugin_name(), libhello_get_plugin_version(), libhello_get_plugin_revision(), libhello_get_plugin_soversion(), libhello_get_plugin_buildtime());

            #ifdef ENABLE_PLUGINS
            printf("%-10s ver. %s, rev. %s, sover. %s (%s)\n", libplugins_get_plugin_name(), libplugins_get_plugin_version(), libplugins_get_plugin_revision(), libplugins_get_plugin_soversion(), libplugins_get_plugin_buildtime());
            #endif
        }

        if ( runAllSections || vm.count("arguments") ) {
            printf(">>  arguments:\n");
            printf("    argc=%d\n", argc);
            for( int i = 0; i < argc; ++i )
            {
                printf( "    argv[%2d] = \"%s\"\n", i, argv[i] );
            }
        }

        if ( runAllSections || vm.count("env") ) {
            printf(">>  environment variables:\n");
            for (const char* const* env = envp; *env != NULL; ++env)
            {
                printf("    %s\n", *env);
            }
        }

        #ifdef ENABLE_PLUGINS
        if ( runAllSections || vm.count("plugins") ) {
            libplugins_init("{}", PluginEventHandler);
            libplugins_deinit();
        }
        #endif

        if ( runAllSections || vm.count("printCompliedInfo") ) {
            libsysinfo_printCompliedInfo();
            libsysinfo_printByteOrderType();
            printf("libsysinfo_isCharSigned=%d\n", libsysinfo_isCharSigned());
        }

        if ( vm.count("verbose") ) {
            verbose = vm["verbose"].as<int>() != 0;
            printf("verbose=%d\n", verbose?1:0);
        }


        if ( vm.count("conversion-mode") ) {
            conversionMode = vm["conversion-mode"].as<std::string>();
        }


        if ( vm.count("input") ) {
            input = vm["input"].as<std::string>();
        }


        if ( vm.count("output") ) {
            output = vm["output"].as<std::string>();
        }


        printf(">>  Appliction Begin\n");


        if ( !input.empty() ) {
            if ( '=' == input[0] ) {
                input.erase(0, 1);
            }
            printf("input=%s\n", input.c_str());
        }


        if ( !output.empty() ) {
            printf("output=%s\n", output.c_str());
        }


        if ( !conversionMode.empty() ) {
            if ( '=' == conversionMode[0] ) {
                conversionMode.erase(0, 1);
            }

            printf("conversion-mode=%s\n", conversionMode.c_str());
            bool result = false;
            FP_ConvertFunc convertFunc = NULL;
            if( 0 == strcmp(conversionMode.c_str(), "hex2bin") ) {
                convertFunc = convertHex2Bin;
            }
            else if( 0 == strcmp(conversionMode.c_str(), "bin2hex") ) {
                convertFunc = convertBin2Hex;
            }
            else {
                printf("Error! There is invalid parameter '--conversion-mode=%s'.\n", conversionMode.c_str());
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
                            printf("Error! There is invalid parameter '--output' (file can't open).\n");
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
                            printf("Error! There is invalid parameter '--input' (file can't open).\n");
                            break;
                        }
                    }

                    std::ostream outstream(pOutputBuf);
                    size_t convertedSize = convertFunc(*pInputStream, outstream, verbose);
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
                printf("Conversion OK!\n");
            }
        }


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


