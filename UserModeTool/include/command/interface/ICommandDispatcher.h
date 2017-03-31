#pragma once

#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class ICommandDispatcher describes a simple command dispatcher.
  *
  * Objects of type ICommandDispatcher receive byte arrays from remote control
  * and send them to their matching ICommandExecuter instance.
  */
class ICommandDispatcher
{
public:
    ICommandDispatcher()          = default;
    virtual ~ICommandDispatcher() = default;

    /**
      * Function receives a bytes array, and sends it to a matching ICommandExecuter
      * instance.
      * It calls the corresponding executer with the tag stripped from the array.
      * @param[in] byte_array - the byte array to use.
      * @param[in] length - the length in bytes of byte_array.
      * @param[in] connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Dispatch(char const *byte_array,
                          uint32_t length,
                          networking::ITCPClient& connection)
    noexcept = 0;
};
}

