#pragma once

#include <vector>
#include <string>

#include "ICommandExecuter.h"
#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class ICommandDispatcher describes a simple command dispatcher.
  *
  * Objects of type ICommandDispatcher commands from input, use the matching
  * ICommandExecuter to translate them to byte arrays, send them to remote tool,
  * and use the ICommandExecuter to process its response.
  */
class ICommandDispatcher
{
public:
    ICommandDispatcher() 		  = default;
    virtual ~ICommandDispatcher() = default;

    /**
      * Use this function to get an ICommandExecuter instance by its name.
      * @param[in] name - a name of a command to find its matching ICommandExecuter.
      * @return If an error occurs, nullptr is returned.
      *         Otherwise, a pointer to the matching instance is returned.
      */
    virtual ICommandExecuter* FindByName(const std::string& name) const noexcept = 0;

    /**
      * Function receives a command, translates it to bytes array, sends it the remote
      * tool using a matching ICommandExecuter and processes the response using
      * the same executer.
      * @param[in] command - the command to use.
      * @param[in] connection - a TCP client to communicate with remote tool.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Dispatch(std::string& command,
                          networking::ITCPClient& connection)
    noexcept = 0;
};
}

