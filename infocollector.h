#ifndef infocollector_h_
#define infocollector_h_


#include <boost/program_options.hpp>


class CInfoCollector{
    public:
        CInfoCollector( bool verbose );
        ~CInfoCollector();

        void trace( const char * fmt, ... ) const;
        void debug( const char * fmt, ... ) const;
        void warning( const char * fmt, ... ) const;
        void error( const char * fmt, ... ) const;
        void fatal( const char * fmt, ... ) const;
        void system( const char * fmt, ... ) const;
        void options( boost::program_options::options_description & desc );
        void setVerbose( bool verbose );

    private:
        bool m_bVerbose;
};

#endif  // end of #ifndef infocollector_h_
