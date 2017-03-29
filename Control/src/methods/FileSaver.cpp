#include "methods/FileSaver.h"

#include <fstream>
#include <cstring>

#include <iostream>
#include <ctime>


using namespace methods;

FileSaver::FileSaver()
{
    buffer = new char[65536];
}

FileSaver::~FileSaver()
{
    delete[] buffer;
}

bool
FileSaver::SaveASingleFile(
    std::string extension,
    std::ios_base::openmode open_mode,
    networking::ITCPClient& connection)
{
    std::string file_name = LocalTimeFileName() + extension;

    std::ofstream output_file(file_name, open_mode);

    while ( true )
    {
        int bytes_received = connection.Recv(buffer, 65536);

        if ( 0 == strncmp(buffer + bytes_received - 3, "o.k", 3) )
        {
            output_file.write(buffer, bytes_received - 3);

            output_file.close();
            return ( true );
        }

        else if ( 0 == strncmp(buffer + bytes_received - 3, "err", 3) )
        {
            output_file.write(buffer, bytes_received - 3);

            output_file.close();
            return ( false );
        }

        else
        {
            output_file.write(buffer, bytes_received);
        }
    }

    return ( true );
}

/* protected */

std::string
FileSaver::LocalTimeFileName()
const
{
    // Current date and time
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y_%I-%M-%S",timeinfo);
    std::string file_name(buffer);

    return ( file_name );
}
