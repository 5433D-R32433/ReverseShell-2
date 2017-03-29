#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "networking/interfaces/ITCPClient.h"


namespace command
{

typedef uint8_t tag_t;

/**
  * Class ICommandExecuter describes a simple command executer.
  *
  * Objects of type ICommandExecuter translate arguments of commands to byte arrays
  * that the remote tool acts according to, and process its response.
  *
  * Each ICommandExecuter instance has its own tag and name (it's up to the programmer to
  * ensure that both are unique to a command), which can be used to reference it.
  */
class ICommandExecuter
{
public:
    ICommandExecuter(tag_t tag, const std::string& name)
        : m_tag(tag),
          m_name(name)
    {}
    virtual ~ICommandExecuter() {}

    /**
      * Function gets a split command and generates its corresponding bytes array.
      * The assumption is that the command is valid.
      * @param command_parts - command from std::in split into separate words.
      *                        As aforementioned, this excludes the command name.
      * @return corresponding byte array.
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

    /**
      * This tag is used to distinguish between different ICommandExecuter instances.
      * It is also used to attribute a bytes array to the correct ICommandExecuter
      * instance.
      */
    const tag_t m_tag;

    /**
      * The command name is used to reach the ICommandExecuter that matches user input.
      * instance.
      */
    const std::string m_name;
};
}
