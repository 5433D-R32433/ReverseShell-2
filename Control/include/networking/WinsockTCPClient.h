#pragma once

#include <winsock2.h>

#include <string>

#include "networking/interfaces/ITCPClient.h"
#include "networking/WinsockTCPSocket.h"


namespace networking
{
/**
  * Class implements a Winsock2 tcp socket client.
  */
class WinsockTCPClient
    : public ITCPClient,
      public WinsockTCPSocket
{
public:

    /**
      * Constructor creates a winsock2 based tcp client
      * and can be used to connect to remote server.
      * @param ip - ip to connect to in "n.n.n.n" format.
                    The parts that make up an address in "." notation can be decimal,
                    octal or hexadecimal as specified in the C language.
      * @param port - port to connect to at remote ip address.
      * @param auto_connect - whether to use constructor to connect (true) or not.
      * @return If no error occurs, connect returns true.
      *         Otherwise, false is returned.
      */
    WinsockTCPClient(const std::string& ip, uint16_t port, bool auto_connect = true);
    WinsockTCPClient(SOCKET socket, struct sockaddr_in addr) :
        WinsockTCPSocket(socket, addr)
    {}
    virtual ~WinsockTCPClient() {}

    int Send(const char *buffer, uint32_t buffer_size);
    int Recv(char *const buffer, uint32_t buffer_size);
    bool Connect();

};
}
