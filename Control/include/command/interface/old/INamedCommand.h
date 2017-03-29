#pragma once

#include <string>
#include <vector>

#include "command/interface/ICommand.h"


namespace command
{
/**
  * An INamedCommand is a uniquely named ICommand.
  *
  * It's up to the class user to make sure each name really is unique.
  * For example, the functionality of "rm -rf" is achievable
  * through an implementation of an ICommand,
  * which in turn is achievable through the command's name - "rm".
  */
class INamedCommand
    : public ICommand
{
public:
    INamedCommand(const std::string& name)
        : m_name(name)
    {}
    virtual ~INamedCommand() {}

    /**
      * The name of the command.
      */
    std::string m_name;

};
}
