#pragma once

#include <string>

#include "networking/interfaces/IClient.h"


namespace networking
{
/**
  * Class describes a basic remote-server client interface,
  * which consists of read/write operations.
  */
class ITCPClient
    : public IClient
{
public:
    ITCPClient()          = default;
    virtual ~ITCPClient() = default;

    /**
      * Function used to connect to a remote tcp server.
      */
    virtual bool Connect()
    noexcept = 0;

};
}
