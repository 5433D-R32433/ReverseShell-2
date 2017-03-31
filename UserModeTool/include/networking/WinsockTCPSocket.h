#pragma once

#include <Winsock2.h>

#include "networking/WinsockAddressedSocket.h"


namespace networking
{
/**
  * Class creates a basic Winsock2 tcp socket.
  */
class WinsockTCPSocket
    : public WinsockAddressedSocket
{
public:
    WinsockTCPSocket()
        : WinsockAddressedSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)
    {}
    WinsockTCPSocket(struct sockaddr_in addr)
        : WinsockAddressedSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, addr)
    {}
    WinsockTCPSocket(SOCKET socket,
                     struct sockaddr_in addr)
        : WinsockAddressedSocket(socket, addr)
    {}
    WinsockTCPSocket(const std::string& ip,
                     uint16_t port)
        : WinsockAddressedSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, ip, port)
    {}

    virtual ~WinsockTCPSocket() = default;
};
}
