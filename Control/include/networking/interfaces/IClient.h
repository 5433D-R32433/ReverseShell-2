#pragma once


namespace networking
{
/**
  * Class describes a basic remote-server client interface,
  * which consists of read/write operations.
  */
class IClient
{
public:
    IClient() {}
    virtual ~IClient() {}

    /**
      * Function used to send data to remote connection.
      * @param buffer - byte array containing the data.
      * @param buffer_size - number of bytes to send out of buffer.
      * @return If no error occurs, send returns the total number of bytes sent.
      *         Otherwise, -1 is returned.
      */
    virtual int Send(const char *buffer, uint32_t buffer_size) = 0;

    /**
      * Function used to receiv data from remote connection.
      * @param buffer - byte array to contain the data.
      * @param buffer_size - maximum number of bytes to read into buffer.
      * @return If no error occurs, recv returns the number of bytes received.
                If the connection has been gracefully closed, the return value is zero.
                Otherwise, -1 is returned.
      */
    virtual int Recv(char *const buffer, uint32_t buffer_size) = 0;
};
}
