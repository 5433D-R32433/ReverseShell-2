#include "command/CommandCollection.h"

#include <memory>

// Each project will include this from his own path
#include "command/interface/ICommandExecuter.h"


using namespace command;

bool
CommandCollection::Add(
    ICommandExecuter* new_command)
noexcept
{
//    if ( !InBounds(new_command->m_tag) )
//        return ( false );

    if ( nullptr != Find(new_command->m_tag) )
        return ( false );

    m_commands[new_command->m_tag] =
        std::unique_ptr<ICommandExecuter>(new_command);

    return ( true );
}

bool
CommandCollection::Remove(
    ICommandExecuter* command_to_remove)
noexcept
{
    if ( nullptr == Find(command_to_remove->m_tag) )
        return ( false );

    /// Removing by tag, so first ensuring both pointers point to same object.
    if ( m_commands[command_to_remove->m_tag].get() != command_to_remove )
        return ( false );

    m_commands[command_to_remove->m_tag].reset();

    return ( true );
}

void
CommandCollection::Clear()
noexcept
{
    for ( auto& command : m_commands )
    {
        command.reset();
    }
}

ICommandExecuter*
CommandCollection::Find(
    tag_t tag)
const noexcept
{
    std::cout << "hi" << '\n';
    return ( m_commands[tag].get() );
}
