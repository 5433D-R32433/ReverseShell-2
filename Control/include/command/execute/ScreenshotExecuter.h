#pragma once

#include "command/interface/ICommandExecuter.h"
#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Objects of type ScreenshotExecuter command the remote tool to
  * send screen shots of local computer back to remote control.
  *
  * Can decide amount of screen shots in a single go,
  * wait time between screen shots,
  * bits per pixel,
  * and whether to encode as PNG.
  */
class ScreenshotExecuter
    : public ICommandExecuter
{
public:
    ScreenshotExecuter(tag_t tag, std::string name)
        : ICommandExecuter(tag, name)
    {}
    virtual ~ScreenshotExecuter() = default;

    std::string ToByteArray(const std::vector<std::string>& command_parts);
    bool ProcessResponse(networking::ITCPClient& connection);

protected:

    /**
    * This struct is used to explicitly address significant addresses
    * inside the received bytes array.
    */
#pragma pack(1)
    typedef struct
    {
        tag_t tag;
        char bits_per_pixel;
        bool png;
        uint32_t captures;
        uint32_t wait_milliseconds;
    } s_Translation;
#pragma pack()

    s_Translation m_lastCommand = { .tag = m_tag };

};
}
