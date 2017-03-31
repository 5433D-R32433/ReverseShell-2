#pragma once

#include "interface/ICommandDispatcher.h"
#include "command/CommandCollection.h"

#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class CommandManager owns a set of commands and implements ICommandDispatcher.
  *
  * It derives from CommandCollection, therefore copy & move operations are forbidden.
  */
class CommandManager
    : public ICommandDispatcher,
      public CommandCollection
{
public:
    CommandManager()          = default;
    virtual ~CommandManager() = default;

    bool Dispatch(char const *byte_array,
                  uint32_t length,
                  networking::ITCPClient& connection)
    noexcept override;

};
}

