#include "infocollector.h"
#include <cstdarg>
#include <termcolor/termcolor.hpp>


CInfoCollector::CInfoCollector( bool verbose )
    : m_bVerbose (verbose)
{

}


CInfoCollector::~CInfoCollector() {

}


void CInfoCollector::trace( const char * fmt, ... ) const {
    if ( m_bVerbose ){
        std::cout << termcolor::white;
        va_list valist;
        va_start(valist, fmt);
        int res = vfprintf(stdout, fmt, valist);
        if ( res <= 0 ) {
            // error
        }
        va_end (valist);
        std::cout << termcolor::reset << std::endl;
    }
}


void CInfoCollector::debug( const char * fmt, ... ) const {
    if ( m_bVerbose ){
        std::cout << termcolor::green;
        va_list valist;
        va_start(valist, fmt);
        int res = vfprintf(stdout, fmt, valist);
        if ( res <= 0 ) {
            // error
        }
        va_end (valist);
        std::cout << termcolor::reset << std::endl;
    }
}


void CInfoCollector::warning( const char * fmt, ... ) const {
    if ( m_bVerbose ){
        std::cout << termcolor::blue;
        va_list valist;
        va_start(valist, fmt);
        int res = vfprintf(stdout, fmt, valist);
        if ( res <= 0 ) {
            // error
        }
        va_end (valist);
        std::cout << termcolor::reset << std::endl;
    }
}


void CInfoCollector::error( const char * fmt, ... ) const {
    std::cerr << termcolor::red;
    va_list valist;
    va_start(valist, fmt);
    int res = vfprintf(stderr, fmt, valist);
    if ( res <= 0 ) {
        // error
    }
    va_end (valist);
    std::cerr << termcolor::reset << std::endl;
}


void CInfoCollector::fatal( const char * fmt, ... ) const {
    std::cerr << termcolor::magenta << termcolor::blink;
    va_list valist;
    va_start(valist, fmt);
    int res = vfprintf(stderr, fmt, valist);
    if ( res <= 0 ) {
        // error
    }
    va_end (valist);
    std::cerr << termcolor::reset << std::endl;
}


void CInfoCollector::system( const char * fmt, ... ) const {
    std::cout << termcolor::cyan;
    va_list valist;
    va_start(valist, fmt);
    int res = vfprintf(stdout, fmt, valist);
    if ( res <= 0 ) {
        // error
    }
    va_end (valist);
    std::cout << termcolor::reset << std::endl;
}


void CInfoCollector::options( boost::program_options::options_description & desc ) {
    std::cout << termcolor::yellow;
    std::streambuf * pOutputBuf = std::cout.rdbuf();
    std::ostream outstream(pOutputBuf);
    desc.print(outstream);
    std::cout << termcolor::reset << std::endl;
}


void CInfoCollector::setVerbose( bool verbose ) {
    m_bVerbose = verbose;
}

