#pragma once

#include "networking/interfaces/IServer.h"
#include "networking/interfaces/ITCPClient.h"

namespace networking
{
/**
  * Class describes a basic TCP server interface.
  */
class ITCPServer
    : public IServer
{
public:
    ITCPServer()          = default;
    virtual ~ITCPServer() = default;

    /**
      * The listen function places a socket in a state
      * in which it is listening for an incoming connection.
      * @param backlong - The maximum length of the queue of pending connections.
      * @return if no error occured, Listen returns true.
                Otherwise, false is returned.
      */
    virtual bool Listen( uint32_t backlog)
    noexcept = 0;

    /**
      * The accept function permits an incoming connection attempt on a socket.
      * @return if no error occured,
                Accept returns a must-be-deleted pointer to ISocket,
                Otherwise, nullptr is returned.
      */
    virtual ITCPClient* Accept()
    noexcept = 0;

};
}
