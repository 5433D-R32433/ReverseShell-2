#pragma once

#include <windows.h>

#include <string>


namespace utils
{
namespace registry
{
/**
  * This class describes a registry editor.
  */
class IRegistryEditor
{
public:
    IRegistryEditor()          = default;
    virtual ~IRegistryEditor() = default;

    /**
      * Use this function to open a registry key.
      * Whether to just open or create if the key
      * doesn't exist is implementation defined.
      * @param[in] key - should be one of the predefined keys:
      *                  HKEY_CLASSES_ROOT
      *                  HKEY_CURRENT_CONFIG
      *                  HKEY_CURRENT_USER
      *                  HKEY_LOCAL_MACHINE
      *                  HKEY_USERS
      *                  Or a key previously opened.
      * @param[in] sub_key - a sub key to concatenate with key.
      * @param[out] result - the opened desired key.
      * @return On success, true is returned.
      *         Otherwise, false is returned.
      */
    virtual bool OpenKey(HKEY key,
                         const std::string& sub_key,
                         PHKEY result)
    const noexcept = 0;

    /**
      * Use this function to open a key and set its value.
      * @param[in] key - should be one of the predefined keys:
      *                  HKEY_CLASSES_ROOT
      *                  HKEY_CURRENT_CONFIG
      *                  HKEY_CURRENT_USER
      *                  HKEY_LOCAL_MACHINE
      *                  HKEY_USERS
      *                  Or a key previously opened.
      * @param[in] sub_key - a sub key to concatenate with key.
      * @param[in] value_name - the key's value name.
      * @param[in] value - the key's value.
      * @return On success, true is returned.
      *         Otherwise, false is returned.
      */
    virtual bool SetValue(HKEY key,
                          std::string sub_key,
                          std::wstring value_name,
                          std::wstring value)
    const noexcept = 0;

};
}
}
