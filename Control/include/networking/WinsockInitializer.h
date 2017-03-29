#pragma once

#include <cstdint>


namespace networking
{
/**
  * Class handles use of the Winsock2 DLL by the calling process.
  *
  * When the first class instance is created, it starts process's usage of Winsock2.
  * When the last instance is deleted, it cleans up.
  */
class WinsockInitializer
{
public:
    /**
      * If the constructor is called for the first time,
      * it initiates use of the Winsock 2 DLL by the process.
      * Otherwise, it does nothing beyond creating the object.
      */
    WinsockInitializer();
    /**
      * If the destructor is called for the last time,
      * it cleans use of the Winsock 2 DLL by the process.
      * Otherwise, it does nothing beyond destroying the object.
      */
    virtual ~WinsockInitializer();
};
}
