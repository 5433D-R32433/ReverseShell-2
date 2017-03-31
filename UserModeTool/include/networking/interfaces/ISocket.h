#pragma once


namespace networking
{
/**
  * Class describes a basic socket interface.
  * A basic socket interface consists of creating a socket,
  * send / receive operations,
  * and a close operation.
  */
class ISocket
{
public:
    ISocket()           = default;
    virtual ~ISocket()  = default;

    /**
      * Function used to close an existing socket.
      * @return If no error occured, Close returns true.
      *         Otherwise, false is returned.
      */
    virtual bool Close()
    noexcept = 0;

};
}
