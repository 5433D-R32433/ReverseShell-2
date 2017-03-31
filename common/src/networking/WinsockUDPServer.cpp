#include "networking/WinsockUDPServer.h"

#include <winsock2.h>

#include <string>

#include "networking/interfaces/ISocket.h"
#include "networking/WinsockUDPSocket.h"


using namespace networking;

bool
WinsockUDPServer::Bind(
    const std::string ip,
    uint16_t port)
noexcept
{
    m_addr = SockAddrIn(ip, port);

    if( SOCKET_ERROR != bind(m_socket, m_addr, sizeof(m_addr)) )
        return ( true );

    m_lastError = WSAGetLastError();

    return ( false );
}

int
WinsockUDPServer::Recvfrom(
    ISocket* from,
    char *const buffer,
    uint32_t buffer_size)
noexcept
{
    struct sockaddr_in from_addr;
    int from_addr_len;

    int recv = recvfrom(m_socket,
                        buffer,
                        buffer_size,
                        0,
                        (struct sockaddr*)&from_addr,
                        &from_addr_len);

    if ( SOCKET_ERROR != recv )
    {
        from = new WinsockUDPSocket(from_addr);

        return ( recv );
    }

    m_lastError = WSAGetLastError();

    return ( -1 );
}

int
WinsockUDPServer::Sendto(
    ISocket* to,
    const char *buffer,
    uint32_t buffer_size)
noexcept
{


    m_lastError = WSAGetLastError();

    return ( -1 );
}


