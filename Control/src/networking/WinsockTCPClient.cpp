#include "networking/WinsockTCPClient.h"

#include <winsock2.h>

#include <string>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace networking;

WinsockTCPClient::WinsockTCPClient(
    const std::string& ip,
    uint16_t port,
    bool auto_connect)
    : WinsockTCPSocket(ip, port)
{
    if( auto_connect )
        Connect();
}

bool
WinsockTCPClient::Connect()
noexcept
{
    if ( connect(m_socket, m_addr, sizeof(m_addr))
            >= 0)
        return ( true );

    m_lastError = WSAGetLastError();

    return ( false );
}

int
WinsockTCPClient::Send(
    const char *buffer,
    uint32_t buffer_size)
noexcept
{
    int sent_size = send(m_socket, buffer, buffer_size, 0);

    if ( SOCKET_ERROR != sent_size )
        return ( sent_size );

    m_lastError = WSAGetLastError();

    return ( -1 );
}

int
WinsockTCPClient::Recv(
    char *const buffer,
    uint32_t buffer_size)
noexcept
{
    int recv_size = recv(m_socket, buffer, buffer_size, 0);

    if ( SOCKET_ERROR != recv_size )
        return ( recv_size );

    std::cout << "error in recv!" << std::endl;
    m_lastError = WSAGetLastError();

    return ( -1 );
}
