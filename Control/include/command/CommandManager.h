#pragma once

#include <array>
#include <cstdint>
#include <limits>

#include "interface/ICommandDispatcher.h"
#include "interface/ICommandExecuter.h"
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

    ICommandExecuter* Find(const std::string& name) const noexcept override;

    bool Dispatch(std::string& command,
                  networking::ITCPClient& connection)
    noexcept override;

};
}

