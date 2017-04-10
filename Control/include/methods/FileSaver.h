#pragma once

#include <fstream>
#include <string>

#include "networking/interfaces/ITCPClient.h"


namespace methods
{
/**
  * Use this class to save a file sent from remote tool.
  */
class FileSaver
{
public:
    FileSaver()
        : m_buffer (new char[65536])
    {}

    virtual ~FileSaver();

    // Copy is forbidden
    FileSaver(const FileSaver& other)            = delete;
    FileSaver& operator=(const FileSaver& other) = delete;

    // Move is defaulted
    FileSaver(FileSaver&& other)            = default;
    FileSaver& operator=(FileSaver&& other) = default;

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
                         networking::ITCPClient& connection)
    noexcept;

protected:

    char *m_buffer;

    /**
      * The name of the file will be the date and time it was saved at.
      * @return the generated name.
      */
    std::string LocalTimeFileName() const noexcept;

};
}
