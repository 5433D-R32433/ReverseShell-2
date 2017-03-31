#pragma once

#include "ITaggedCommand.h"
// Each project will include this from his own path
#include "command/interface/ICommandExecuter.h"


namespace command
{
/**
  * Class ICommandCollection describes a collection of ICommandExecuters.
  *
  * The class receives ICommandExecuters that were created using
  * operator new, and deletes them internally on destruction.
  */
class ICommandCollection
{
public:
    ICommandCollection()          = default;
    virtual ~ICommandCollection() = default;

    /**
      * Function receives a pointer to an ICommandExecuter which was created
      * using operator new and adds it to its table if its tag isn't already used.
      * @param[in] new_command - a pointer to a command instance which was
      *                          created with the 'new' operator.
      * @param[in] command_name - a name for the new command to reference.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Add(ICommandExecuter* new_command) noexcept = 0;

    /**
      * Function receives a pointer to an ICommandExecuter which was created
      * using operator new, deletes it, and removes it from this instance's table.
      * @param[in] command_to_remove - a pointer to a command instance that was
      *                            created with the 'new' operator.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Remove(ICommandExecuter* command_to_remove) noexcept = 0;

    /**
      * Function deletes and removes all pointers to ICommandExecuters
      * held by the object.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      *         An example error in Clear is when wanting to avoid deletion of
      *         a shared ptr.
      */
    virtual void Clear() noexcept = 0;

   /**
     * Use this function to get an ICommandExecuter by its tag.
     * Only delete the returned object using ICommandCollection::Remove.
     * @param[in] tag - a tag to find its matching ITaggedCommand.
     * @return If an error occurs, nullptr is returned.
     *         Otherwise, a pointer to the matching instance is returned.
     */
   virtual ICommandExecuter* Find(tag_t tag) const noexcept = 0;

};
}
