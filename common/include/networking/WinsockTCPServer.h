#pragma once

#include "networking/interfaces/ITCPServer.h"
#include "networking/interfaces/ITCPClient.h"
#include "networking/WinsockTCPSocket.h"

namespace networking
{
/**
  * Class implements a basic TCP server using Winsock2.
  */
class WinsockTCPServer :
    public ITCPServer,
    public WinsockTCPSocket
{
public:
    WinsockTCPServer()
        : WinsockTCPSocket()
    {}
    virtual ~WinsockTCPServer() = default;

    bool Bind(const std::string ip,
              uint16_t port)
    noexcept override;

    bool Listen( uint32_t backlog)
    noexcept override;

    ITCPClient* Accept()
    noexcept override;

};
}
