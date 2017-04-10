#include <iostream>
#include <memory>
#include <cstdio>

#include "networking/WinsockInitializer.h"
#include "networking/WinsockTCPServer.h"
#include "networking/interfaces/ITCPClient.h"

#include "command/CommandManager.h"
#include "utils/builders.h"


int main(int argc, char *argv[], char *envp[])
{
    networking::WinsockInit();

    networking::WinsockTCPServer connection;
    connection.Bind("192.168.1.17", 12121);
    connection.Listen(1);

    auto dispatcher = utils::builders::BuildManager();

    auto client = connection.Accept();

    std::cerr << "Received connection" << std::endl;

    std::string command;

    while ( 0 != command.compare("exit") )
    {
        std::cout << ">> ";
        getline(std::cin, command);

        dispatcher->Dispatch(command, *client);
    }

    networking::WinsockCleanup();

    return ( 0 );
}
