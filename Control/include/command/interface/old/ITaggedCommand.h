#pragma once

#include <string>
#include <vector>

#include "command/interface/ICommand.h"


namespace command
{

typedef uint8_t tag_t;

/**
  * An ITaggedCommand is a tagged INamedCommand.
  *
  * An ITaggedCommand instance uses ITaggedCommand::m_tag
  * when implementing ICommand::ToByteArray
  * in order to create its unique byte array pattern,
  * and let the remote tool distinguish between different commands.
  */
class ITaggedCommand
    : public ICommand
{
public:

    /**
      * The constructor stores a tag as m_tag.
      * @param tag - the requested tag to use.
      * @param name -
      */
    ITaggedCommand(tag_t tag)
        : m_tag(tag)
    {}
    virtual ~ITaggedCommand() {}

    /**
      * The unique tag described in main class's description.
      */
    const tag_t m_tag;

};
}
