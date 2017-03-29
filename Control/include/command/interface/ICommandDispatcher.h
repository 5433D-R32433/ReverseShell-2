#pragma once

#include <vector>
#include <string>

#include "command/interface/ICommandExecuter.h"
#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Class ICommandDispatcher describes a simple command processor.
  *
  * Objects of type ICommandDispatcher commands from input, use the matching
  * ICommandExecuter to translate them to byte array, send it to remote tool,
  * and use the same ICommandExecuter to process its response.
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
      * @param[in] command_name - a name for the new command to reference.
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
      * Use this function to get an ICommandExecuter instance by its name.
      * @param[in] name - a name of a command to find its matching ICommandExecuter.
      * @return If an error occurs, nullptr is returned.
      *         Otherwise, a pointer to the matching instance is returned.
      */
    virtual ICommandExecuter* Find(std::string name) const = 0;

    /**
      * Function receives a command, translates it to bytes array, sends it the remote
      * tool using a matching ICommandExecuter and processes the response using
      * the same executer.
      * @param[in] command - the command to use.
      * @param[in] connection - a TCP client to communicate with remote tool.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    virtual bool Dispatch(std::string& command,
                          networking::ITCPClient& connection) = 0;
};
}

