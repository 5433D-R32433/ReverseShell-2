#include "methods/driver/Installer.h"
#include "methods/driver/SCManager.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


using namespace methods::driver;

const std::string&
Installer::SysFile()
const
{
    return ( m_sys_file );
}

unsigned long
Installer::Install()
const
{
    SCManager sc_manager;

    sc_manager.CreateService(m_sys_file);
    sc_manager.StartService(m_sys_file);

    return ( 1 );
}

unsigned long
Installer::Uninstall()
const
{
    SCManager sc_manager;

    sc_manager.StopService(m_sys_file);
    sc_manager.DeleteService(m_sys_file);

    return ( 1 );
}
