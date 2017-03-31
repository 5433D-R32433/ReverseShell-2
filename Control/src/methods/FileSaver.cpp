#include "methods/FileSaver.h"

#include <fstream>
#include <cstring>

#include <iostream>
#include <ctime>


using namespace methods;

FileSaver::~FileSaver()
{
    delete m_buffer;
}

bool
FileSaver::SaveASingleFile(
    std::string extension,
    std::ios_base::openmode open_mode,
    networking::ITCPClient& connection)
noexcept
{
    std::string file_name = LocalTimeFileName() + extension;

    std::ofstream output_file(file_name, open_mode);

    while ( true )
    {
        int bytes_received = connection.Recv(m_buffer, 65536);

        if ( 0 == strncmp(m_buffer + bytes_received - 3, "o.k", 3) )
        {
            output_file.write(m_buffer, bytes_received - 3);

            output_file.close();
            return ( true );
        }

        else if ( 0 == strncmp(m_buffer + bytes_received - 3, "err", 3) )
        {
            output_file.write(m_buffer, bytes_received - 3);

            output_file.close();
            return ( false );
        }

        else
        {
            output_file.write(m_buffer, bytes_received);
        }
    }

    return ( true );
}

/* protected */

std::string
FileSaver::LocalTimeFileName()
const noexcept
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
