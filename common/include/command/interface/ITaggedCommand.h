#pragma once

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


namespace command
{

using tag_t = uint8_t;

/**
  * @brief Derive from this class to mark a command with a tag.
  *
  * The tag can be used to distinguish between different commands.
  * In such case, It's up to the user to ensure the tag is unique.
  */
class ITaggedCommand
{
public:
    ITaggedCommand(tag_t tag)
        : m_tag(tag)
    {}

    virtual ~ITaggedCommand()
    {
#ifdef _DEBUG
        std::cout << "ITaggedCommand::~ITaggedCommand()\n";
#endif // _DEBUG
    }

    /**
      * The described tag.
      */
    const tag_t m_tag;
};
}
