#pragma once

#include <Winsock2.h>

#include "networking/interfaces/ISocket.h"


namespace networking
{
/**
  * Class is a wrapper for Winsock2 socket.
  *
  * This should be the base class for any Winsock2 socket implementation.
  */
class BasicWinsockSocket
    : public ISocket
{
public:

    BasicWinsockSocket(int address_family,
                       int type,
                       int protocol);
    BasicWinsockSocket(SOCKET socket);

    /**
      * The destructor closes the socket without checking for errors.
      */
    virtual ~BasicWinsockSocket();

    /**
      * Use this function to clse the socket.
      */
    bool Close() noexcept override;

    /**
      * Function used to return an instance's last WSA error.
      */
    int LastWSAError() const noexcept;

protected:

    /**
      * The underlying socket structure.
      */
    SOCKET m_socket;

    /**
      * Latest WSA error.
      */
    int m_lastError;

};
}
