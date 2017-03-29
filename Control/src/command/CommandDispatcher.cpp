#include "command/CommandDispatcher.h"

#ifdef _DEBUG
#include <iostream>
#include <stdexcept>
#endif // _DEBUG

#include <vector>
#include <string>

#include "utils/string.h"


using namespace command;

CommandDispatcher::~CommandDispatcher()
{
    Clear();
}

//CommandDispatcher::CommandDispatcher(
//    CommandDispatcher& other)
//{
//    swap(*this, other);
//}
//
//CommandDispatcher& CommandDispatcher::operator=(
//    CommandDispatcher other)
//{
//    swap(*this, other);
//
//    return ( *this );
//}

bool
CommandDispatcher::Add(
    ICommandExecuter* new_command)
{
    if ( !InBounds(new_command->m_tag) )
        return ( false );

    if ( nullptr != Find(new_command->m_tag) )
        return ( false );

    m_commands[new_command->m_tag] = new_command;

    return ( true );
}

bool
CommandDispatcher::Remove(
    ICommandExecuter *command_to_remove)
{
    if ( nullptr == Find(command_to_remove->m_tag) )
        return ( false );

    /// Removing by tag, so first ensuring both pointers point to same object.
    if ( m_commands[command_to_remove->m_tag] != command_to_remove )
        return ( false );

    m_commands[command_to_remove->m_tag] = nullptr;
    delete command_to_remove;

    return ( true );
}

ICommandExecuter*
CommandDispatcher::Find(
    tag_t tag)
const
{
    if ( !InBounds(tag) )
        return ( nullptr );

    return ( m_commands[tag] );
}

ICommandExecuter*
CommandDispatcher::Find(
    std::string name)
const
{
    for ( ICommandExecuter* const& command : m_commands )
    {
        if ( nullptr == command )
            continue;

        if ( 0 == command->m_name.compare(name) )
            return ( command );
    }

    return ( nullptr );
}

bool
CommandDispatcher::Clear()
{
    for ( ICommandExecuter* const& command : m_commands )
    {
        if ( nullptr == command)
            continue;

        Remove(command);
    }

    return ( true );
}

bool
CommandDispatcher::Dispatch(
    std::string& command,
    networking::ITCPClient& connection)
{
    // Split
    std::vector<std::string> command_parts = utils::string::Split(command, " ");

    if ( command_parts.size() < 1 )
        return ( false );

    // Find executer by command name
    ICommandExecuter *executer = Find(command_parts[0]);

    if ( nullptr == executer )
        return ( false );

    // Send byte array
    std::string byte_array = executer->ToByteArray(command_parts);

    if ( byte_array.size() !=
            (unsigned)connection.Send(byte_array.data(), byte_array.size()) )
        return ( false );

    // Process response
    bool success = executer->ProcessResponse(connection);

    return ( success );
}

/* protected */

bool
CommandDispatcher::InBounds(
    tag_t tag)
const
{
    return ( 0 <= tag && tag <= m_commands.size() );
}
