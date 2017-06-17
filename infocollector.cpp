#include "infocollector.h"
#include <cstdarg>
#include <cstdio>
#include <string>
#include <iostream>


// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


CInfoCollector::CInfoCollector( bool verbose )
    : m_bVerbose (verbose)
{

}


CInfoCollector::~CInfoCollector() {

}


void CInfoCollector::debug( const char * fmt, ... ) const {
    if ( m_bVerbose ){
        va_list valist;
        va_start(valist, fmt);
        std::string newFmt(ANSI_COLOR_GREEN);
        newFmt.append(fmt);
        newFmt.append(ANSI_COLOR_RESET);
        newFmt.append("\n");
        int res = vfprintf(stdout, newFmt.c_str(), valist);
        if ( res <= 0 ) {
            // error
        }
        va_end (valist);
    }
}


void CInfoCollector::error( const char * fmt, ... ) const {
    va_list valist;
    va_start(valist, fmt);
    std::string newFmt(ANSI_COLOR_RED);
    newFmt.append(fmt);
    newFmt.append(ANSI_COLOR_RESET);
    newFmt.append("\n");
    int res = vfprintf(stderr, newFmt.c_str(), valist);
    if ( res <= 0 ) {
        // error
    }
    va_end (valist);
}


void CInfoCollector::system( const char * fmt, ... ) const {
    va_list valist;
    va_start(valist, fmt);
    std::string newFmt(ANSI_COLOR_CYAN);
    newFmt.append(fmt);
    newFmt.append(ANSI_COLOR_RESET);
    newFmt.append("\n");
    int res = vfprintf(stdout, newFmt.c_str(), valist);
    if ( res <= 0 ) {
        // error
    }
    va_end (valist);
}


void CInfoCollector::options( boost::program_options::options_description & desc ) {
    std::cout << ANSI_COLOR_YELLOW;
    std::streambuf * pOutputBuf = std::cout.rdbuf();
    std::ostream outstream(pOutputBuf);
    desc.print(outstream);
    std::cout << ANSI_COLOR_RESET << std::endl;
}


void CInfoCollector::setVerbose( bool verbose ) {
    m_bVerbose = verbose;
}

