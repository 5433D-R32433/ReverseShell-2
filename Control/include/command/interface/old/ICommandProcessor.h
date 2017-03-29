#pragma once

#include <string>

#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class ICommandProcessor describes a simple command processor.
  *
  * Objects of type ICommandProcessor receive user-typed commands,
  * send them to the remote tool,
  * and process their response.
  */
class ICommandProcessor
{
public:
    ICommandProcessor() {}
    virtual ~ICommandProcessor() {}

    /**
      * Function handles a command in cooperation with remote tool
      * as described in main class's description.
      * @param[in] command - a user-typed command.
      * @param[in] connection - a tcp client to communicate with remote tool.
      * @return If no error occurs, function returns true.
      *         Otherwise, function returns false.
      */
    virtual bool Process(const std::string& command, networking::ITCPClient& connection) const = 0;

};
}

