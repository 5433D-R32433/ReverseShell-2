#include "command/CommandManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <vector>
#include <string>

#include "utils/string.h"
#include "command/interface/ICommandExecuter.h"


using namespace command;

ICommandExecuter*
CommandManager::FindByName(
    const std::string& name)
const noexcept
{
    for ( const auto& command : m_commands )
    {
        if ( (nullptr != command.get()) && command->m_name == name)
        {
            return ( command.get() );
        }
    }

    return ( nullptr );
}

bool
CommandManager::Dispatch(
    std::string& command,
    networking::ITCPClient& connection)
noexcept
{
    // Split
    std::vector<std::string> command_parts = utils::string::Split(command, " ");

    if ( command_parts.size() < 1 )
        return ( false );

    // Find executer by command name
    ICommandExecuter *executer = FindByName(command_parts[0]);

    if ( nullptr == executer )
        return ( false );

    // Send byte array
    std::string byte_array = executer->ToByteArray(command_parts);

    if ( byte_array.size() > 0 && byte_array.size() !=
            (unsigned)connection.Send(byte_array.data(), byte_array.size()) )
        return ( false );

    // Process response
    bool success = executer->ProcessResponse(connection);

    return ( success );
}
