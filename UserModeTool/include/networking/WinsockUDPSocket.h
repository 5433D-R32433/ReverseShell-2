#pragma once

#include <winsock2.h>

#include "networking/WinsockAddressedSocket.h"


namespace networking
{
/**
  * Class creates a basic Winsock2 udp socket.
  */
class WinsockUDPSocket
    : public WinsockAddressedSocket
{
public:
    WinsockUDPSocket()
        : WinsockAddressedSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
    {}
    WinsockUDPSocket(struct sockaddr_in addr)
        : WinsockAddressedSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, addr)
    {}
    WinsockUDPSocket(const std::string& ip, uint16_t port)
        : WinsockAddressedSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, ip, port)
    {}
    virtual ~WinsockUDPSocket() = default;

};
}
