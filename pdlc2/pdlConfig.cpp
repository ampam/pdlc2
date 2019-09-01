#include "stdafx.h"
#include "pdlConfig.h"

using namespace web;
using namespace pam::pdl::config;
namespace fs = boost::filesystem;

PdlConfig::PdlConfig( int argc, char* argv[] )
{
//    std::wstring fileName;

    if ( argc > 4 )
    {
        _fileName = argv[ 1 ];
        /*
        std::wstring templateFolder = argv[ 2 ];
        std::wstring classTemplate = argv[ 3 ];
        std::wstring outputFolder = argv[ 4 ];
        */

        
        _config[L"in"] = json::value::string( PdlConfig::to_wstring( argv[ 2 ] ) );
        _config[L"classTemplate"] = json::value::string( PdlConfig::to_wstring( argv[ 3 ] ) );
        _config[L"out"] = json::value::string( PdlConfig::to_wstring( argv[ 4 ] ) );
        _config[L"indent"] = json::value::string( L"    " );
        _config[L"file"] = json::value();

        
        if ( argc == 6 )
        {
            _config[L"configFile"] = json::value::string( PdlConfig::to_wstring( argv[ 5 ] ) );
	        const auto configFile = readConfigFile();
            _config[L"file"] = configFile;
        }

        _isValid = true;
    }
    else
    {
        _isValid = false;
    }

}


PdlConfig::~PdlConfig(void)
{
}


web::json::value PdlConfig::readConfigFile()
{
    web::json::value result;

	auto configFile = fs::path( _config[L"configFile"].as_string() );

    if ( fs::exists( configFile ) )
    {
        std::ifstream in( configFile.string(), std::ios_base::in );
        std::string jsonString;

        std::copy(
            std::istream_iterator<char>( in ),
            std::istream_iterator<char>(),
            std::back_inserter( jsonString ) );

	    const auto jsonWString = PdlConfig::to_wstring( jsonString );

		result = web::json::value::parse( jsonWString );

        std::wistringstream stream( jsonWString );
		//std::wistringstream stream;
		//stream.str( jsonWString );
		//result = web::json::value::parse( stream );

        stream >> result;
    }
    else
    {
        std::cerr << "Warning! Can't read config file: " << configFile.string() << std::endl;
    }

    return result;

}

