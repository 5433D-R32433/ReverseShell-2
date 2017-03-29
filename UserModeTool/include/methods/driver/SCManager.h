#pragma once

#include <windows.h>
#include <functional>


namespace methods
{
namespace driver
{
/**
  * Use this class to associate with sc.exe .
  * The .sys file must be in the current working directory.
  *
  * Error codes are returned from GetLastError(). 0 means success.
  * https://msdn.microsoft.com/en-us/library/windows/desktop/ms679360(v=vs.85).aspx
  */
class SCManager
{
public:
    SCManager(LPCTSTR lpMachineName     = nullptr,
              LPCTSTR lpDatabaseName    = nullptr,
              DWORD   dwDesiredAccess   = SC_MANAGER_ALL_ACCESS)
        : m_machineName(lpMachineName),
          m_databaseName(lpDatabaseName),
          m_desiredAccess(dwDesiredAccess)
    {}
    virtual ~SCManager() {}

    /**
      * Use this function to get a handle to the Windows' SCManager.
      *
      * @return On success, returns a handle to SCManager.
      *         Othereise, returns NULL.
      */
    SC_HANDLE Open() const;

    /**
      * Use this function to create a service from a .sys file.
      * The .sys file must be in the current working directory.
      * The name of the service will be the same as the .sys file,
      * including the extension.
      *
      * @param[in] sys_file - the .sys file name.
      * @return error code.
      */
    unsigned long CreateService (const std::string& sys_file) const;

    /**
      * Use this function to start an existing service.
      *
      * @param[in] sys_file - the .sys file name.
      * @return error code.
      */
    unsigned long StartService  (const std::string& sys_file) const;

    /**
      * Use this function to stop a running service.
      *
      * @param[in] sys_file - the .sys file name.
      * @return error code.
      */
    unsigned long StopService   (const std::string& sys_file) const;

    /**
      * Use this function to delete an existing service.
      *
      * @param[in] sys_file - the .sys file name.
      * @return error code.
      */
    unsigned long DeleteService (const std::string& sys_file) const;

private:

    /// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684323(v=vs.85).aspx
    LPCTSTR m_machineName;
    LPCTSTR m_databaseName;
    DWORD   m_desiredAccess;

    using Implementor = std::function<unsigned long(SC_HANDLE,
                                                    const std::string&)>;

    /**
      * Creates an SC_HANDLE using Open() and checks for its result.
      * If failed then returns error,
      * Otherwise calls the implementor with the handle and returns
      * its result.
      * This is to avoid code duplications (calling open
      * and checking result).
      * @param[in] func - an implementor function.
      * @return error code
      */
    unsigned long FunctionCall(Implementor func,
                               const std::string& sys_file) const;

    /**
      * This function implements service creation.
      * @param[in] sc_handle - a handle to Windows' SCManager.
      * @return error code.
      */
    unsigned long CreateServiceImpl (SC_HANDLE sc_handle,
                                     const std::string& sys_file) const;

    /**
      * This function implements service launching.
      * @param[in] sc_handle - a handle to Windows' SCManager.
      * @return error code.
      */
    unsigned long StartServiceImpl  (SC_HANDLE sc_handle,
                                     const std::string& sys_file) const;

    /**
      * This function implements service termination.
      * @param[in] sc_handle - a handle to Windows' SCManager.
      * @return error code.
      */
    unsigned long StopServiceImpl   (SC_HANDLE sc_handle,
                                     const std::string& sys_file) const;

    /**
      * This function implements service deletion.
      * @param[in] sc_handle - a handle to Windows' SCManager.
      * @return error code.
      */
    unsigned long DeleteServiceImpl (SC_HANDLE sc_handle,
                                     const std::string& sys_file) const;

    /**
      * Use this function to get the current state of a service.
      * Available states can be viewed in MSDN:
      * https://msdn.microsoft.com/en-us/library/windows/desktop/ms685992(v=vs.85).aspx
      *
      * @param[in] service - a handle to the service.
      * @return On success, service's state is returned.
      *         Otherwise, 0 is returned.
      */
    DWORD GetCurrentServiceState(SC_HANDLE service) const;

    /**
      * Use this function to fill a process status information structure.
      * for a service.
      *
      * @param[in] service - a handle to the service.
      * @param[out] service_status - a pointer to a destination struct.
      * @return - On success, true is returned.
      *           Otherwise, false is returned.
      */
    bool  GetServiceStatus      (SC_HANDLE service,
                                 SERVICE_STATUS_PROCESS *service_status) const;
    /**
      * Use this function to wait for a service to hit a certain state.
      *
      * @param[in] service - a handle to the service.
      * @param[in] operation - a state to wait for service to hit.
      * @param[in] milliseconds - maximum time to wait in milliseconds.
      */
    bool WaitForPendingOperation(SC_HANDLE service,
                                 DWORD operation,
                                 DWORD milliseconds) const;
};
}
}
