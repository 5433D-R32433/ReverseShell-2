#pragma once

#include <string>


namespace methods
{
namespace driver
{
/**
  * Use this class to install a .sys file.
  * The .sys file must be in the current working directory.
  *
  * Error codes are returned from GetLastError(). 0 means success.
  * https://msdn.microsoft.com/en-us/library/windows/desktop/ms679360(v=vs.85).aspx
  */
class Installer
{
public:
    Installer(const std::string& sys_file)
        : m_sys_file(sys_file)
    {}
    virtual ~Installer() = default;

    /**
      * Use this function to get the sys file path.
      * @return path of sys file the object is associated with.
      */
    const std::string& SysFile() const;

    /**
      * Use this function to install the sys file whose path was
      * given to the constructor.
      * @return error code
      */
    unsigned long Install() const;

    /**
      * Use this function to uninstall the sys file whose path was
      * given to the constructor.
      * @return error code
      */
    unsigned long Uninstall() const;

private:

    /**
      * The name of the .sys file.
      */
    const std::string m_sys_file;

};
}
}
