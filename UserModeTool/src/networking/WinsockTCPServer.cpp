#include "networking/WinsockTCPServer.h"
#include "networking/WinsockTCPClient.h"
#include "networking/SockAddrIn.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

using namespace networking;

bool
WinsockTCPServer::Bind(
    const std::string ip,
    uint16_t port)
{
    m_addr = SockAddrIn(ip, port);

    if( SOCKET_ERROR != bind(m_socket,m_addr, sizeof(m_addr)) )
        return ( true );

    m_lastError = WSAGetLastError();

    return ( false );
}

bool
WinsockTCPServer::Listen(
    uint32_t backlog)
{
    if( SOCKET_ERROR != listen(m_socket, backlog) )
        return ( true );

    m_lastError = WSAGetLastError();

    return ( false );
}

ITCPClient*
WinsockTCPServer::Accept()
{
//    struct sockaddr_in new_sockaddr;
    SockAddrIn new_sockaddr;
    int new_sockaddr_size;
    SOCKET new_socket = accept(m_socket,
//                               (struct sockaddr*)&new_sockaddr,
                               new_sockaddr,
                               &new_sockaddr_size);

    if( INVALID_SOCKET != new_socket )
    {
        return ( new WinsockTCPClient(new_socket, new_sockaddr) );
    }

#ifdef _DEBUG
    std::cerr << "error in accept" << std::endl;
#endif // _DEBUG

    m_lastError = WSAGetLastError();

    return ( nullptr );
}
