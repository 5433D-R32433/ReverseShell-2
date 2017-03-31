#pragma once

#include <winsock2.h>

#include <string>

#include "networking/interfaces/IClient.h"
#include "networking/WinsockUDPSocket.h"


namespace networking
{
/**
  * Class implements a Winsock2 udp socket client.
  */
class WinsockUDPClient
    : public IClient,
      public WinsockUDPSocket
{
public:

    /**
      * In addition of socket initialization,
      * the constructor initializes remote destination address.
      * @param ip - ip to send to in "n.n.n.n" format.
                    The parts that make up an address in "." notation can be decimal,
                    octal or hexadecimal as specified in the C language.
      * @param port - port to send to at remote ip address.
      * @return If failed, saves last error code which is to be retrieved by BasicWinsockSocket::LastWSAError.
      */
    WinsockUDPClient(const std::string& ip, uint16_t port)
        : WinsockUDPSocket(ip, port)
    {}
    virtual ~WinsockUDPClient() = default;

    int Send(const char *buffer, uint32_t buffer_size) noexcept override;
    int Recv(char *const buffer, uint32_t buffer_size) noexcept override;

};
}
