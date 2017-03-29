#include "networking/WinsockUDPClient.h"

#include <winsock2.h>

#include <string>


using namespace networking;

int
WinsockUDPClient::Send(
    const char *buffer,
    uint32_t buffer_size)
{
    int sent_size = sendto(m_socket,
                           buffer,
                           buffer_size,
                           0,
                           (SOCKADDR*)&m_addr,
                           sizeof(m_addr));

    if ( SOCKET_ERROR != sent_size )
        return ( sent_size );

    m_lastError = WSAGetLastError();

    return ( -1 );
}

int
WinsockUDPClient::Recv(
    char *const buffer,
    uint32_t buffer_size)
{
    int size_;
    int recv_size = recvfrom(m_socket,
                             buffer,
                             buffer_size,
                             0,
                             (SOCKADDR*)&m_addr,
                             &size_);

    if ( SOCKET_ERROR != recv_size )
        return ( recv_size );

    m_lastError = WSAGetLastError();

    return ( -1 );
}
