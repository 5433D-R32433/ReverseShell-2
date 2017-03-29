#pragma once

#include "networking/interfaces/IServer.h"
#include "networking/interfaces/ISocket.h"

namespace networking
{
/**
  * Class describes a basic TCP server interface.
  */
class IUDPServer
    : public IServer
{
public:
    IUDPServer() {}
    ~IUDPServer() {}

    /**
      * The Recvfrom function receives a datagram and stores the source address.
      * @param[out] from - a pointer to ISocket to store remote address.
      * @param[out] buffer - byte array to contain the data.
      * @param[in] buffer_size - maximum number of bytes to read into buffer.
      * @return If no error occurs, Recvfrom returns the number of bytes received.
                Otherwise, -1 is returned.
      */
    virtual int Recvfrom(ISocket* from, char *const buffer, uint32_t buffer_size) = 0;

    /**
      * The Sendto function sends data to a specific destination.
      * @param[in] to - a pointer to ISocket to send buffer through.
      * @param[in] buffer - byte array containing the data.
      * @param[in] buffer_size - number of bytes to send out of buffer.
      * @return If no error occurs, send returns the total number of bytes sent.
      *         Otherwise, -1 is returned.
      */
    virtual int Sendto(ISocket* to, const char *buffer, uint32_t buffer_size) = 0;

};
}

