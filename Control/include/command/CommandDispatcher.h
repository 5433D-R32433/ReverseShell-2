#pragma once

#include <array>
#include <cstdint>
#include <limits>

#include "command/interface/ICommandDispatcher.h"
#include "command/interface/ICommandExecuter.h"

#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class CommandDispatcher implements ICommandDispatcher.
  *
  * It uses an array of pointers to ICommandExecuter, each in its
  * equals-to-its-tag index.
  *
  * Only a single instance of this class should manage a certain pointer
  * to an ICommandExecuter.
  */
class CommandDispatcher
    : ICommandDispatcher
{
public:
    CommandDispatcher() = default;
    virtual ~CommandDispatcher();

//    /**
//      * The copy constructor removes ownership of pointers from source.
//      */
//    CommandDispatcher(CommandDispatcher& other);
//
//    /**
//      * The move assignment operator removes ownership of pointers from source.
//      */
//    CommandDispatcher& operator=(CommandDispatcher other);
//
//    /**
//      * Swap functionality.
//      */
//    friend void swap(CommandDispatcher& first, CommandDispatcher& second) // nothrow
//    {
//        using std::swap;
//
//        swap(first.m_commands, second.m_commands);
//    }

    bool Add(ICommandExecuter* new_command);
    bool Remove(ICommandExecuter *command_to_remove);
    ICommandExecuter* Find(tag_t tag) const;
    ICommandExecuter* Find(std::string name) const;
    bool Clear();
    bool Dispatch(std::string& command,
                  networking::ITCPClient& connection);

protected:

    /**
      * Copy constructor is forbidden.
      */
    CommandDispatcher(const CommandDispatcher& other) = delete;

    /**
      * Assignment operator is forbidden.
      */
    CommandDispatcher& operator=(const CommandDispatcher& other) = delete;

    /**
      * The implementation uses the remote control's tag
      * that was set as the first byte of the bytes array
      * as an index in this array of pointers to ICommandExecuters.
      *
      * This array is zero initialized.
      */
    std::array<ICommandExecuter*, std::numeric_limits<tag_t>::max()+1> m_commands = {};

    /**
      * Function specifies whether a tag is in table bounds.
      * @param[in] tag - a tag to determine whether is in bounds or not.
      * @return If tag is in bounds, true is returned.
      *         Otherwise, false is returned.
      */
    bool InBounds(tag_t tag) const;

};
}

