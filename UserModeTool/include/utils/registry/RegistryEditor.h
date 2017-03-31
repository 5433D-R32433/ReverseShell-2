#pragma once

#include <windows.h>

#include <string>

#include "utils/registry/IRegistryEditor.h"


namespace utils
{
namespace registry
{
/**
  *
  */
class RegistryEditor
    : public IRegistryEditor
{
public:
    RegistryEditor()          = default;
    virtual ~RegistryEditor() = default;

    /**
      * This function creates the key if it doesn't exist.
      */
    bool OpenKey(HKEY key,
                 const std::string& sub_key,
                 PHKEY result)
    const noexcept override;

    bool SetValue(HKEY key,
                  std::string sub_key,
                  std::wstring value_name,
                  std::wstring value)
    const noexcept override;

private:

    /**
      * This function just creates a registry key.
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
    bool CreateKey(HKEY key,
                   LPCSTR sub_key,
                   PHKEY result)
    const noexcept;

    /**
      * This function just opens a registry key.
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
    bool OpenExistingKey(HKEY key,
                         LPCSTR sub_key,
                         PHKEY result)
    const noexcept;

    /**
      * This function just opens a value to a registry key.
      * @param[in] key - an opened registry key.
      * @param[in] value_name - the key's value name.
      * @param[in] value - the key's value.
      * @return On success, true is returned.
      *         Otherwise, false is returned.
      */
    bool SetValueImpl(HKEY hkey,
                      PCWSTR value_name,
                      PCWSTR value)
    const noexcept;
};
}
}
