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

//    std::unique_ptr<command::CommandManager> dispatcher(
//        utils::builders::BuildManager());

    command::CommandManager *dispatcher = utils::builders::BuildManager();
    command::ICommandExecuter* a = dispatcher->Find(0);
    std::cout << a->m_name << '\n';

    connection.Bind("192.168.1.17", 12121);
    connection.Listen(1);

    std::unique_ptr<networking::ITCPClient> client(
        connection.Accept());

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
