#include "methods/driver/SCManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <cstdio>
#include <windows.h>
#include <functional>


using namespace methods::driver;
using namespace std::placeholders;

SC_HANDLE
SCManager::Open()
const
{
    return (
               OpenSCManager(m_machineName,
                             m_databaseName,
                             m_desiredAccess)
           );
}

unsigned long
SCManager::CreateService(
    const std::string& sys_file)
const
{
#ifdef _DEBUG
    std::cerr << "Creating service: " << sys_file << '\n';
#endif // _DEBUG

    return ( FunctionCall(
                 std::bind(&SCManager::CreateServiceImpl, this, _1, _2),
                 sys_file)
           );
}

unsigned long
SCManager::StartService(
    const std::string& sys_file)
const
{
#ifdef _DEBUG
    std::cerr << "Starting service: " << sys_file << '\n';
#endif // _DEBUG

    return ( FunctionCall(
                 std::bind(&SCManager::StartServiceImpl, this, _1, _2),
                 sys_file)
           );
}

unsigned long
SCManager::StopService(
    const std::string& sys_file)
const
{
#ifdef _DEBUG
    std::cerr << "Stopping service: " << sys_file << '\n';
#endif // _DEBUG

    return ( FunctionCall(
                 std::bind(&SCManager::StopServiceImpl, this, _1, _2),
                 sys_file)
           );
}

unsigned long
SCManager::DeleteService(
    const std::string& sys_file)
const
{
#ifdef _DEBUG
    std::cerr << "Deleting service: " << sys_file << '\n';
#endif // _DEBUG

    return ( FunctionCall(
                 std::bind(&SCManager::DeleteServiceImpl, this, _1, _2),
                 sys_file)
           );
}

/* private */

unsigned long
SCManager::FunctionCall(
    Implementor func,
    const std::string& sys_file)
const
{
    SC_HANDLE sc_handle = Open();

    if ( nullptr == sc_handle )
        return ( GetLastError() );

    return ( func(sc_handle, sys_file) );
}

unsigned long
SCManager::CreateServiceImpl (
    SC_HANDLE sc_handle,
    const std::string& sys_file)
const
{
    // Get full .sys file path
    char current_directory[128];
    GetCurrentDirectory(128, current_directory);

    std::string full_path =
//        "\"" +
        std::string(current_directory) + "\\" + sys_file;
//         + "\"";

#ifdef _DEBUG
    std::cerr << full_path << '\n';
#endif // _DEBUG

    // Create service
    // Function from Windows.h
    SC_HANDLE service = ::CreateService(sc_handle,
                                        sys_file.c_str(),
                                        sys_file.c_str(),
                                        SERVICE_ALL_ACCESS,
                                        SERVICE_KERNEL_DRIVER,
                                        SERVICE_DEMAND_START,
                                        SERVICE_ERROR_NORMAL,
                                        full_path.c_str(),
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL,
                                        NULL);

    if ( NULL == service )
    {
#ifdef _DEBUG
    std::cerr << "Failed to create the service.\n";
#endif // _DEBUG

        CloseServiceHandle(sc_handle);

        return ( GetLastError() );
    }

    CloseServiceHandle(sc_handle);
    CloseServiceHandle(service);

    return ( 0 );
}

unsigned long
SCManager::StartServiceImpl (
    SC_HANDLE sc_handle,
    const std::string& sys_file)
const
{
    // Get a handle to the service.
    SC_HANDLE service = OpenService(
                            sc_handle,
                            sys_file.c_str(),
                            SERVICE_ALL_ACCESS);

    if ( NULL == service )
    {
#ifdef _DEBUG
        std::cerr << "Couldn't open service.\n";
#endif // _DEBUG

        CloseServiceHandle(sc_handle);

        return ( GetLastError() );
    }

    unsigned long err_code = 0;

    // If service is already running then error
    switch ( GetCurrentServiceState(service) )
    {
    case SERVICE_STOPPED:
//    case SERVICE_STOP_PENDING:
        break;

    default:
#ifdef _DEBUG
        std::cerr << "Service state not 'stopped'.\n";
#endif // _DEBUG

        goto error;
    }

    // Attempt to start the service
    if ( !::StartService(
                service,
                0,
                NULL) )
    {
#ifdef _DEBUG
        std::cerr << "Couldn't start the service.\n";
#endif // _DEBUG

        goto error;
    }

    // Wait for service to be running
    // Wait for max 10 seconds
    if ( true == WaitForPendingOperation(service, SERVICE_RUNNING, 10000) )
        goto exit;

#ifdef _DEBUG
    std::cerr << "Failed to start the service.\n";
#endif // _DEBUG

error:
    err_code = GetLastError();

exit:

    CloseServiceHandle(service);
    CloseServiceHandle(sc_handle);

    return ( err_code );
}

unsigned long
SCManager::StopServiceImpl (
    SC_HANDLE sc_handle,
    const std::string& sys_file)
const
{
    // Get a handle to the service.
    SC_HANDLE service = OpenService(
                            sc_handle,
                            sys_file.c_str(),
                            SERVICE_ALL_ACCESS);

    if ( NULL == service )
    {
        CloseServiceHandle(sc_handle);

        return ( GetLastError() );
    }

    unsigned long err_code = 0;

    SERVICE_STATUS_PROCESS service_status;

    // Send a stop
    if ( 0 == ControlService(
                service,
                SERVICE_CONTROL_STOP,
                (LPSERVICE_STATUS) &service_status ) )
    {
        goto error;
    }

    // Wait for service to be stopped
    // Wait for max 10 seconds
    if ( true == WaitForPendingOperation(service, SERVICE_STOPPED, 10000) )
        goto exit;

error:
    err_code = GetLastError();

exit:

    CloseServiceHandle(service);
    CloseServiceHandle(sc_handle);

    return ( err_code );
}

unsigned long
SCManager::DeleteServiceImpl (
    SC_HANDLE sc_handle,
    const std::string& sys_file)
const
{
    unsigned long err_code = 0;

    SC_HANDLE service = ::OpenService(sc_handle,
                                      sys_file.c_str(),
                                      DELETE);
    if ( nullptr == service )
    {
#ifdef _DEBUG
        std::cout << "Failed to open the service." << '\n';
#endif // _DEBUG

        CloseServiceHandle(sc_handle);

        return ( GetLastError() );
    }

    if ( FALSE == ::DeleteService(service) )
    {
#ifdef _DEBUG
        std::cout << "Failed to delete the service." << '\n';
#endif // _DEBUG

        err_code = GetLastError();
    }

    CloseServiceHandle(service);
    CloseServiceHandle(sc_handle);

    return ( err_code );
}

DWORD
SCManager::GetCurrentServiceState(
    SC_HANDLE service)
const
{
    SERVICE_STATUS_PROCESS service_status;

    if ( false == GetServiceStatus(service, &service_status) )
    {
        return ( 0 );
    }

    return ( service_status.dwCurrentState );
}

bool
SCManager::GetServiceStatus(
    SC_HANDLE service,
    SERVICE_STATUS_PROCESS *service_status)
const
{
    DWORD dwBytesNeeded;

    if ( 0 == QueryServiceStatusEx(service,
                                   SC_STATUS_PROCESS_INFO,
                                   (LPBYTE) service_status,
                                   sizeof(SERVICE_STATUS_PROCESS),
                                   &dwBytesNeeded ) )
    {
        return ( false );
    }

    return ( true );
}

bool
SCManager::WaitForPendingOperation(
    SC_HANDLE service,
    DWORD operation,
    DWORD milliseconds)
const
{
    for( uint32_t i = 0; i < milliseconds / 10; ++i )
    {
        // Check status every 10 ms
        Sleep(10);

        if ( operation == GetCurrentServiceState(service) )
        {
            return ( true );
        }
    }

    return ( false );
}
