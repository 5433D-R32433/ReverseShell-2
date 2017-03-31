#pragma once

#include <winsock2.h>

#include <string>


namespace networking
{
class SockAddrIn
{
public:
    SockAddrIn() {}
    SockAddrIn(const std::string& ip, uint16_t port);
    SockAddrIn(uint16_t sin_family, unsigned long ip_network_order, uint16_t port);
    SockAddrIn(struct sockaddr_in sin)
        : m_sin(sin)
    {}
    virtual ~SockAddrIn() {}

    operator struct sockaddr_in() noexcept;
    operator struct sockaddr_in*() noexcept;
    operator struct sockaddr*() noexcept;

private:
    struct sockaddr_in m_sin;
};
}
