#pragma once

#include "command/interface/ICommandExecuter.h"
#include "networking/interfaces/ITCPClient.h"

namespace command
{
/**
  * Class ICommandDispatcher describes a simple command processor.
  *
  * Objects of type ICommandDispatcher receive byte arrays from remote control
  * and send them to their matching ICommandExecuter instance.
  *
  * The class internally manages instances of types derived from ICommandExecuter,
  * that were created outside the class with operator new, and will be deleted inside.
  */
class ICommandDispatcher
{
public:
    ICommandDispatcher() {}
    virtual ~ICommandDispatcher() {}

    /**
      * Function receives a pointer to an ICommandExecuter instance which was created
      * using operator new and adds it to its table if its tag isn't already used.
      * @param[in] new_command - a pointer to an ICommandExecuter instance which was
      *                          created with the 'new' operator.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Add(ICommandExecuter* new_command) = 0;

    /**
      * Function receives a pointer to an ICommandExecuter instance which was created
      * using operator new, deletes it, and removes it from this instance's table.
      * @param[in] command_to_remove - a pointer to an ICommandExecuter instance that was
      *                            created with the 'new' operator.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Remove(ICommandExecuter *command_to_remove) = 0;

    /**
      * Function deletes and removes all pointers to ICommandExecuter
      * an instance of this class holds.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      *         An example error in Clear is when wanting to avoid deletion of
      *         a shared ptr.
      */
    virtual bool Clear() = 0;

    /**
      * Use this function to get an ICommandExecuter instance by its tag.
      * @param[in] tag - a tag to find its matching ICommandExecuter.
      * @return If an error occurs, nullptr is returned.
      *         Otherwise, a pointer to the matching instance is returned.
      */
    virtual ICommandExecuter* Find(tag_t tag) const = 0;

    /**
      * Function receives a bytes array, and sends it to a matching ICommandExecuter
      * instance.
      * It calls the corresponding executer with the tag stripped from the array.
      * @param[in] byte_array - the byte array to use.
      * @param[in] length - the length in bytes of byte_array.
      * @param[in] connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Dispatch(char const *byte_array,
                          uint32_t length,
                          networking::ITCPClient& connection) = 0;
};
}

