#include "networking/WinsockInitializer.h"

#include <winsock2.h>

#include <stdexcept>


using namespace networking;

WinsockInitializer::WinsockInitializer()
{
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    int err = WSAStartup(wVersionRequested, &wsaData);

    if ( err )
    {
        throw std::runtime_error("WSA init failed");
    }
}

WinsockInitializer::~WinsockInitializer()
{
    WSACleanup();
}
