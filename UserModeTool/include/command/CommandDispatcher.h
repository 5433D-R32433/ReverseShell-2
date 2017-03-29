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
  */
class CommandDispatcher
    : ICommandDispatcher
{
public:
    CommandDispatcher() = default;
    virtual ~CommandDispatcher();

    bool Add(ICommandExecuter* new_command);
    bool Remove(ICommandExecuter *command_to_remove);
    ICommandExecuter* Find(tag_t tag) const;
    bool Clear();
    bool Dispatch(char const *byte_array,
                  uint32_t length,
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
      * as an index in this array of pointers to ICommandExecuter.
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

