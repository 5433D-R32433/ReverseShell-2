#pragma once

#include <array>
#include <limits>
#include <memory>

#include "interface/ICommandCollection.h"
#include "command/interface/ITaggedCommand.h"
// Each project will include this from his own path
#include "command/interface/ICommandExecuter.h"


namespace command
{
/**
  * This class implements a collection of ITaggedCommands.
  * It uses an array of pointers to ITaggedCommand, each in its
  * equals-to-its-tag index.
  *
  * Only a single instance of this class should manage a certain pointer
  * to an ITaggedCommand.
  *
  * Copy & move operations are forbidden.
  */
class CommandCollection
    : ICommandCollection
{
public:
    CommandCollection()          = default;
    virtual ~CommandCollection() = default;

	// Copy is forbidden
	CommandCollection(const CommandCollection& other) 			 = delete;
	CommandCollection& operator=(const CommandCollection& other) = delete;

	// Move is defaulted
	CommandCollection(CommandCollection&& other) 	  			 = default;
	CommandCollection& operator=(CommandCollection&& other) 	 = default;

    bool Add(ICommandExecuter* new_command) 		 noexcept override;
    bool Remove(ICommandExecuter *command_to_remove) noexcept override;
    void Clear() 									 noexcept override;
    ICommandExecuter* Find(tag_t tag) 		   const noexcept override;

protected:

    using pointer_type = std::shared_ptr<ICommandExecuter>;

	/**
	  * The underlying table.
	  * Objects will be deleted with object's destruction.
	  */
    std::array<pointer_type,
               std::numeric_limits<tag_t>::max()+1> m_commands = {};
};
}
