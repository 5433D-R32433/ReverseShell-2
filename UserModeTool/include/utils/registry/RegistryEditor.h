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
      *
      */
    bool CreateKey(HKEY key,
                   LPCSTR sub_key,
                   PHKEY result)
    const noexcept;

    /**
      *
      */
    bool OpenExistingKey(HKEY key,
                         LPCSTR sub_key,
                         PHKEY result)
    const noexcept;

    /**
      *
      */
    bool SetValueImpl(HKEY hkey,
                      PCWSTR value_name,
                      PCWSTR value)
    const noexcept;
};
}
}
