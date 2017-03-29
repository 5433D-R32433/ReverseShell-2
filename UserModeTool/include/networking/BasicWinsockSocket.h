#pragma once

#include <Winsock2.h>

#include <string>

#include "networking/interfaces/ISocket.h"
#include "networking/SockAddrIn.h"
#include "networking/WinsockInitializer.h"

namespace networking
{
/**
  * @brief Class creates a basic Winsock2 socket.
  *
  * This is the base class for any Winsock2 implementation,
  * therefore it uses a static WinsockInitializer instance
  * to handle usage of the Winsock2 DLL by the process.
  *
  * This WinsockInitializer instance is created upon
  * the first call to any of the constructors of this class,
  * and destroyed with the last instance of this class.
  */
class BasicWinsockSocket
    : public ISocket,
      private WinsockInitializer
{
public:

    BasicWinsockSocket(int address_family,
                       int type,
                       int protocol);
    BasicWinsockSocket(SOCKET socket);
    virtual ~BasicWinsockSocket();

    bool Close();

    /**
      * Function used to return an instance's last WSA error.
      */
    int LastWSAError() const;

protected:

    /**
      * The underlying socket structure.
      */
    SOCKET m_socket;

    /**
      * Latest WSA error of an instance.
      */
    int m_lastError;

    /**
      * A static variable used to count instances of WinsockInitializer.
      */
    static uint32_t m_numberOfInstances;

    /**
      * @brief A static variable used to initialize and
      * clean up usage of the Winsock2 DLL by the process.
      *
      * This variable is constructed with the first call to any of
      * the constructors of the this class, and destroyed with the
      * last instance of this class.
      */
    static WinsockInitializer *winsockInitializer;

};
}
