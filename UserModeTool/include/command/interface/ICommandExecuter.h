#pragma once

#include <cstdint>

#include "networking/interfaces/ITCPClient.h"
#include "command/interface/ITaggedCommand.h"


namespace command
{
/**
  * Class ICommandExecuter describes a simple byte array processor.
  *
  * Objects of type ICommandExecuter receive arrays of bytes from remote control,
  * use them to do their designated local processing,
  * and return a matching response.
  *
  * Each ICommandExecuter instance has its own tag (it's up to the programmer to ensure
  * that each tag is unique), which is used to deliver a bytes array to its corresponding
  * ICommandExecuter instance.
  */
class ICommandExecuter
    : public ITaggedCommand
{
public:
    ICommandExecuter(tag_t tag)
        : ITaggedCommand(tag)
    {}

    virtual ~ICommandExecuter() = default;

    /**
      * Function receives a bytes array, does its designated local processing,
      * and returns a response to remote control.
      * @param[in] byte_array - the byte array to use.
      * @param[in] length - the length in bytes of byte_array.
      * @param[in] connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Execute(char const *byte_array,
                         uint32_t length,
                         networking::ITCPClient& connection)
    noexcept = 0;

};
}
