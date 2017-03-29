#include "networking/BasicWinsockSocket.h"

#include <Winsock2.h>

#include <string>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace networking;

uint32_t BasicWinsockSocket::m_numberOfInstances = 0;
WinsockInitializer *BasicWinsockSocket::winsockInitializer = nullptr;

BasicWinsockSocket::BasicWinsockSocket(
    int address_family,
    int type,
    int protocol)
{
    if ( 0 == m_numberOfInstances++ )
        winsockInitializer = new WinsockInitializer();

    m_socket = socket(address_family, type, protocol);

    if ( INVALID_SOCKET == m_socket )
        m_lastError = WSAGetLastError();
    else
        m_lastError = 0;
}

BasicWinsockSocket::BasicWinsockSocket(
    SOCKET socket)
{
    if ( 0 == m_numberOfInstances++ )
        winsockInitializer = new WinsockInitializer();

    m_socket = socket;
}

BasicWinsockSocket::~BasicWinsockSocket()
{
    this->Close();

    if ( 0 == --m_numberOfInstances )
        delete winsockInitializer;
}

bool
BasicWinsockSocket::Close()
{
    return ( 0 == closesocket(m_socket) );
}

int
BasicWinsockSocket::LastWSAError()
const
{
    return ( m_lastError );
}

