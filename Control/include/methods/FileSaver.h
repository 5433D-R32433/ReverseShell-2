#pragma once

#include "networking/interfaces/ITCPClient.h"
#include <fstream>


namespace methods
{
class FileSaver
{
public:
    FileSaver();
    virtual ~FileSaver();

    /**
      * This function saves a single file that is received from remote tool.
      * The name of the file will be the date and time it was saved at..
      * @param[in] extension - the extension of the file name.
      * @param[in] open_mode - the mode to open the file in.
      * @param[in] connection -a TCP client to communicate with remote tool.
      * @return If the screen shot was fully received and saved, true is returned.
      *         Otherwise, false is returned.
      */
    bool SaveASingleFile(std::string extension,
                         std::ios_base::openmode open_mode,
                         networking::ITCPClient& connection);

protected:

    char *buffer;

    /**
      * The name of the file will be the date and time it was saved at.
      * @return the generated name.
      */
    std::string LocalTimeFileName() const;

};
}
