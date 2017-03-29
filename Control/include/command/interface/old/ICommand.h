#pragma once

#include <string>
#include <vector>

#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class ICommand describes a simple command processor.
  *
  * Objects of type ICommand translate a user typed command
  *	to a corresponding byte array that's to be sent to the remote tool,
  * and are able to handle its response.
  */
class ICommand
{
public:
    ICommand() {}
    virtual ~ICommand() {}

    /**
      * Function gets a split command and generates its corresponding bytes array.
      * There's an assumption the command was validated.
      * @param command_parts - command from std::in split into separate words.
      * @return corresponding byte array
      */
    virtual std::string ToByteArray(const std::vector<std::string>& command_parts) = 0;

    /**
      * Function handles the remote tool's response to the previously sent bytes array
		of same ICommand instance.
      * @param connection - a tcp client to receive the response from.
      * @return If response processing was successful, function returns true.
				Otherwise, false is returned.
      */
    virtual bool ProcessResponse(networking::ITCPClient& connection) = 0;

};
}
