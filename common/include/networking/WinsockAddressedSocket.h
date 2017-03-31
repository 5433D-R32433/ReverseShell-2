#pragma once

#include <Winsock2.h>

#include <string>

#include "networking/interfaces/ISocket.h"
#include "networking/SockAddrIn.h"
#include "networking/BasicWinsockSocket.h"

namespace networking
{
/**
  * Class creates an addressed Winsock2 socket.
  * This type of socket consists of a SOCKET and a struct sockaddr_in class members.
  */
class WinsockAddressedSocket
    : public BasicWinsockSocket
{
public:

    /**
      * Constructor initialized the SOCKET struct using BasicWinsockSocket constructor,
      * and default initializes the struct sockaddr_in member.
      */
    WinsockAddressedSocket(int address_family,
                           int type,
                           int protocol)
        : BasicWinsockSocket(address_family, type, protocol)
    {}

    WinsockAddressedSocket(int address_family,
                           int type,
                           int protocol,
                           const std::string& ip,
                           uint16_t port)
        : BasicWinsockSocket(address_family, type, protocol),
          m_addr(ip, port)
    {}

    WinsockAddressedSocket(int address_family,
                           int type,
                           int protocol,
                           uint16_t sin_family,
                           unsigned long ip_network_order,
                           uint16_t port)
        : BasicWinsockSocket(address_family, type, protocol),
          m_addr(sin_family, ip_network_order, port)
    {}

    WinsockAddressedSocket(int address_family,
                           int type,
                           int protocol,
                           struct sockaddr_in sin)
        : BasicWinsockSocket(address_family, type, protocol),
          m_addr(sin)
    {}

    WinsockAddressedSocket(SOCKET socket,
                           struct sockaddr_in sin)
        : BasicWinsockSocket(socket),
          m_addr(sin)
    {}

    WinsockAddressedSocket()          = default;
    virtual ~WinsockAddressedSocket() = default;

protected:

    /**
      * A multipurpose buffer that contains the address of a connection entity.
      * For example, UDP and TCP clients will use to contain remote destination address,
      * and UDP and servers will use it as an address to bind to.
      */
    SockAddrIn m_addr;

};
}
