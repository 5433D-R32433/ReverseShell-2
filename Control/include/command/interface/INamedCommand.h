#pragma once

#include <string>


namespace command
{
/**
  * @brief Derive from this class to name a command.
  *
  * The name can be used to translate user input to a matching
  * ICommandTranslator.
  */
class INamedCommand
{
public:
    INamedCommand(std::string name)
        : m_name(name)
    {}

    virtual ~INamedCommand() = default;

    /**
      * The described tag.
      */
    const std::string m_name;
};
}
