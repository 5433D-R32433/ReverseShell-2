#include "networking/WinsockInitializer.h"

#include <winsock2.h>

#include <mutex>


static std::mutex init_mutex;
static std::mutex clean_mutex;
static bool initialized = false;

int
networking::WinsockInit()
{
    std::lock_guard<std::mutex> lock(init_mutex);

    if ( !initialized )
    {
        initialized = true;
        WORD wVersionRequested = MAKEWORD(2, 2);
        WSADATA wsaData;
        return ( WSAStartup(wVersionRequested, &wsaData) );
    }

    return ( 0 );
}

int
networking::WinsockCleanup()
{
    std::lock_guard<std::mutex> lock(clean_mutex);

    if ( initialized )
    {
        return ( WSACleanup() );
    }

    return ( 0 );
}
