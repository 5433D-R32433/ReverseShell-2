#pragma once

#include "networking/interfaces/IUDPServer.h"
#include "networking/WinsockUDPSocket.h"


namespace networking
{
/**
  * Class implements a basic UDP server using Winsock2.
  */
class WinsockUDPServer
    : public IUDPServer,
      public WinsockUDPSocket
{
public:
    WinsockUDPServer() :
        WinsockUDPSocket()
    {}
    virtual ~WinsockUDPServer() {}

    bool Bind(const std::string ip, uint16_t port);

    int Sendto  (ISocket* to,   const char *buffer, uint32_t buffer_size);
    int Recvfrom(ISocket* from, char *const buffer, uint32_t buffer_size);

};
}
