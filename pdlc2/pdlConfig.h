#pragma once

namespace pam { namespace pdl { namespace config {

class PdlConfig
{
private:
    web::json::value _config;

    bool _isValid;

    std::string _fileName;
    std::string _templateFolder;
    std::string _outputFolder;
    std::string _classTemplate;
    std::string _configFolder;

    web::json::value readConfigFile();


public:
    PdlConfig( int argc, char* argv[] );
    ~PdlConfig(void);

    web::json::value& getJsonConfig() { return _config; }

    bool isValid() const { return _isValid; }

    std::string getInputFileName() const { return _fileName; }

    static std::string to_string( std::wstring const& value )
    {
        // std::string result;
        // result.assign( value.begin(), value.end() );

        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;

        std::string result = converter.to_bytes( value );
        
        return result;
    }

    static std::wstring to_wstring( std::string const& value )
    {
        std::wstring result;
        result.assign( value.begin(), value.end() );
        return result;
    }

    static std::wstring to_wstring( char const* value )
    {
        const std::string sValue = value;
        auto result = PdlConfig::to_wstring( sValue );
        return result;
    }

    static bool as_bool( web::json::value& value, const char* key, bool defaultValue = false )
    {
        auto result = defaultValue;

        const auto wsKey = PdlConfig::to_wstring( key );

        if ( value.has_field( wsKey ) )
        {
            result = value[ wsKey ].as_bool();
        }
        return result;
    }

    static std::vector<web::json::value> as_array(web::json::value& value, const char* key)
    {
        std::vector<web::json::value> result;

        const auto wsKey = PdlConfig::to_wstring( key );

        if (value.has_field( wsKey ) )
        {
            auto arrayValue = value[wsKey].as_array();
            auto iter = arrayValue.begin();
            while( iter != arrayValue.end() )
            {
                result.push_back( *iter );
                ++iter;
            }
        }
        return result;
    }

    static std::string as_string( web::json::value& value, const char* key )
    {
        std::string result;

        const auto wsKey = PdlConfig::to_wstring( key );

        if ( value.has_field( wsKey ) )
        {
            result = PdlConfig::to_string( value[ wsKey ].as_string() );
        }
        return result;
    }

    static int as_int( web::json::value& value, const char* key )
    {
        auto result = 0;

        const auto wsKey = PdlConfig::to_wstring( key );

        if ( value.has_field( wsKey ) )
        {
            result = value[ wsKey ].as_integer();
        }
        return result;
    }

    
};

}}};

