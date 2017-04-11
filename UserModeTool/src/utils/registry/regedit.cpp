#include "utils/registry/regedit.h"

#include <windows.h>

#include <iostream>
#include <string>

const Regkey::container Regkey::root_keys = {
        HKEY_CLASSES_ROOT,
        HKEY_CURRENT_CONFIG,
        HKEY_CURRENT_USER,
        HKEY_LOCAL_MACHINE,
        HKEY_USERS
    };

Regkey
Regkey::operator[](
    std::string extension)
const noexcept
{
    return ( Regkey(m_rootKey,
                    m_subKey.empty() ? m_valueName : m_subKey + "\\" + m_valueName,
                    std::move(extension) ));
}

const std::string&
Regkey::operator=(
    const std::string& value)
const noexcept
{
    call(&Regkey::setimpl, value);

    return ( value );
}

std::string
Regkey::get()
const
{
    DWORD sz = 2048;
    std::array<BYTE, 2048> buffer;

    if ( ERROR_SUCCESS != call(&Regkey::getimpl, buffer.data(), &sz) )
    {

    }

    return ( std::string(reinterpret_cast<char*>(buffer.data())) );
}

bool
Regkey::create()
const noexcept
{
    HKEY key;

    return ( ERROR_SUCCESS == openimpl(&key) ||
             ERROR_SUCCESS == createimpl(&key) );
}

bool
Regkey::remove()
const noexcept
{
    return ( ERROR_SUCCESS == RegDeleteKey(m_rootKey, m_subKey.c_str()) );
}

/* private */

LONG
Regkey::openimpl(PHKEY result)
const noexcept
{
    return  (
              RegOpenKeyEx(m_rootKey,
                           m_subKey.c_str(),
                           0,
                           (KEY_WRITE | KEY_READ),
                           result )
            );
}

LONG
Regkey::createimpl(PHKEY result)
const noexcept
{
    return (
            RegCreateKeyEx(m_rootKey,
                           m_subKey.c_str(),
                           0,
                           NULL,
                           0,
                           KEY_ALL_ACCESS,
                           NULL,
                           result,
                           NULL)
           );
}

LONG
Regkey::setimpl(
    HKEY key,
    const std::string& value)
const noexcept
{
    return (
            RegSetValueEx(
                          key,
                          reinterpret_cast<LPCSTR>(m_valueName.c_str()),
                          0,
                          REG_SZ,
                          reinterpret_cast<const BYTE*>(value.c_str()),
                          (value.size()+1) * sizeof(std::string::value_type))
           );
}

LONG
Regkey::getimpl(
    HKEY key,
    BYTE* buffer,
    DWORD* psize)
const noexcept
{
    return (
            RegQueryValueEx(
                key,
                reinterpret_cast<LPCSTR>(m_valueName.c_str()),
                NULL,
                NULL,
                buffer,
                psize)
           );
}

template<typename Func, typename... Args>
LONG
Regkey::call(Func&& func, Args&&... args)
const noexcept
{
    HKEY key;
    openimpl(&key);

    LONG errcode = (this->*func)(key, std::forward<Args>(args)...);

    RegCloseKey(key);

    return ( errcode );
}
