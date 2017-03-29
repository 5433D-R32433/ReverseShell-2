#include "utils/registry/RegistryEditor.h"

#include <Windows.h>


using namespace utils::registry;

bool
RegistryEditor::OpenKey(
    HKEY key,
    const std::string& sub_key,
    PHKEY result)
const noexcept
{
    return ( OpenExistingKey(key, sub_key.c_str(), result) ||
             CreateKey(key, sub_key.c_str(), result) );
}


bool
RegistryEditor::SetValue(
    HKEY key,
    std::string sub_key,
                          std::wstring value_name,
                          std::wstring value)
const noexcept
{
    HKEY reg_key;

    if ( false == OpenKey(key, sub_key, &reg_key) )
    {
        return ( false );
    }

    if ( SetValueImpl(reg_key, value_name.c_str(), value.c_str()) )
    {
        return ( false );
    }

    if ( ERROR_SUCCESS != RegCloseKey(reg_key) )
    {
        return ( false );
    }

    return ( true );
}

/* private */

bool
RegistryEditor::CreateKey(
    HKEY key,
    LPCSTR sub_key,
    PHKEY result)
const noexcept
{
    return ( ERROR_SUCCESS == RegCreateKeyEx(key, sub_key, 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, result, NULL) );
}

bool
RegistryEditor::OpenExistingKey(
    HKEY key,
    LPCSTR sub_key,
    PHKEY result)
const noexcept
{
    return ( ERROR_SUCCESS == RegOpenKeyEx(key, sub_key, 0, (KEY_WRITE | KEY_READ), result) );
}

bool
RegistryEditor::SetValueImpl(
    HKEY hkey,
    PCWSTR value_name,
    PCWSTR value)
const noexcept
{
    DWORD size = (wcslen(value) + 1) * 2;
    return ( 0 == RegSetValueExW(hkey, value_name, 0, REG_SZ, (BYTE*)value, size) );
}
