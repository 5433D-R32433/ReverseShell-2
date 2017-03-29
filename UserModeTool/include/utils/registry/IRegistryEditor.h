#pragma once

#include <windows.h>

#include <string>


namespace utils
{
namespace registry
{
/**
  *
  */
class IRegistryEditor
{
public:
    IRegistryEditor()          = default;
    virtual ~IRegistryEditor() = default;

    /**
      *
      */
    virtual bool OpenKey(HKEY key,
                         const std::string& sub_key,
                         PHKEY result)
    const noexcept = 0;

    /**
      *
      */
    virtual bool SetValue(HKEY key,
                          std::string sub_key,
                          std::wstring value_name,
                          std::wstring value)
    const noexcept = 0;

};
}
}
