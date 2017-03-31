#include "networking/BasicWinsockSocket.h"

#include <Winsock2.h>

#include <string>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace networking;

BasicWinsockSocket::BasicWinsockSocket(
    int address_family,
    int type,
    int protocol)
{
    m_socket = socket(address_family, type, protocol);

    if ( INVALID_SOCKET == m_socket )
        m_lastError = WSAGetLastError();
    else
        m_lastError = 0;
}

BasicWinsockSocket::BasicWinsockSocket(
    SOCKET socket)
{
    m_socket = socket;
}

BasicWinsockSocket::~BasicWinsockSocket()
{
    this->Close();
}

bool
BasicWinsockSocket::Close()
noexcept
{
    return ( 0 == closesocket(m_socket) );
}

int
BasicWinsockSocket::LastWSAError()
const noexcept
{
    return ( m_lastError );
}

