#include "networking/SockAddrIn.h"

#include <winsock2.h>


using namespace networking;

SockAddrIn::SockAddrIn(
   const std::string& ip,
   uint16_t port)
   : SockAddrIn(AF_INET, inet_addr(ip.c_str()), htons(port))
{}

SockAddrIn::SockAddrIn(
   uint16_t sin_family,
   unsigned long ip_network_order,
   uint16_t port)
{
   m_sin.sin_family = sin_family;
   m_sin.sin_addr.s_addr = ip_network_order;
   m_sin.sin_port = port;
}

SockAddrIn::operator struct sockaddr_in()
noexcept
{
   return ( m_sin );
}
SockAddrIn::operator struct sockaddr_in*()
noexcept
{
   return ( &m_sin );
}
SockAddrIn::operator struct sockaddr*()
noexcept
{
   return ( (struct sockaddr*)&m_sin );
}

//SockAddrIn::operator ()(const std::string ip&, uint16_t port)
//{
//
//}
