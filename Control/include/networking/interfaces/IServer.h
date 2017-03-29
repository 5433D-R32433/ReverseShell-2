#pragma once

#include <string>


namespace networking
{
/**
  * Class describes a basic server interface.
  */
class IServer
{
public:
    IServer() {}
    ~IServer() {}

    /**
      * Associate A local address with server connection.
      * @param ip - ip to bind to in "n.n.n.n" format.
                    The parts that make up an address in "." notation can be decimal,
                    octal or hexadecimal as specified in the C language.
      * @param port -
      */
    virtual bool Bind(const std::string ip, uint16_t port) = 0;

};
}
