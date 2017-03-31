#include "command/CommandManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include "command/interface/ICommandExecuter.h"


using namespace command;

bool
CommandManager::Dispatch(
    char const *byte_array,
    uint32_t length,
    networking::ITCPClient& connection)
noexcept
{
    if ( length < sizeof(tag_t) )
        return ( false );

    ICommandExecuter *command = Find(*(tag_t*) byte_array);

    if ( nullptr == command )
        return ( false );

    // Skip the tag
    byte_array += sizeof(tag_t);
    length     -= sizeof(tag_t);

    bool success = command->Execute(byte_array, length, connection);

    return ( success );
}
