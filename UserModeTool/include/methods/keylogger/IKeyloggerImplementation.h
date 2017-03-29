#pragma once

#include <string>


namespace methods
{
namespace keylogger
{
/**
  * This class describes an interface to a keylogger
  * that logs to a file.
  * Derived types implement this logging interface.
  */
class IKeyloggerImplementation
{
public:
    IKeyloggerImplementation(std::string file_name)
        : m_fileName(file_name)
    {}
    virtual ~IKeyloggerImplementation() {}

    /**
      * This function saves key strokes at the time
      * it is called.
      */
    virtual void KeystrokeSavingRoutine() = 0;

    /**
      * This function opens log file in append mode.
      */
    virtual void AppendLog() = 0;

    /**
      * This function creates an empty log file.
      */
    virtual void RestartLog() = 0;

    /**
      * Use this function to get the name of the log
      * file.
      * @return name of log file.
      */
    std::string GetFileNameS()
    {
        return ( m_fileName );
    }

    /**
      * Use this function to get the name of the log
      * file.
      * @return name of log file.
      */
    char const * GetFileNameC()
    {
        return ( m_fileName.c_str() );
    }

protected:

    /**
      * The name (including an extension) of the log file.
      */
    const std::string m_fileName;

};
}
}
