#include "command/CommandDispatcher.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace command;

CommandDispatcher::~CommandDispatcher()
{
    Clear();
}

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
    char const *byte_array,
    uint32_t length,
    networking::ITCPClient& connection)
{
    if ( length < sizeof(tag_t) )
        return ( false );

    ICommandExecuter *command = Find(*(tag_t*) byte_array);

    if ( nullptr == command )
        return ( false );

    byte_array += sizeof(tag_t);
    length     -= sizeof(tag_t);

    bool success = command->Execute(byte_array, length, connection);

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
