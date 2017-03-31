#pragma once

#include "command/interface/ICommandExecuter.h"
#include "methods/screenshot/BmpScreenshot.h"
#include "networking/interfaces/ITCPClient.h"


namespace command
{
/**
  * Objects of type ScreenshotExecuter send screen shots of local computer
  * to remote control.
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
    ScreenshotExecuter(tag_t tag)
        : ICommandExecuter(tag)
    {}
    virtual ~ScreenshotExecuter() = default;

    bool Execute(char const *byte_array,
                 uint32_t length,
                 networking::ITCPClient& connection)
    noexcept override;

protected:

    /**
    * This struct is used to explicitly address significant addresses
    * inside the received bytes array.
    */
#pragma pack(1)
    typedef struct
    {
        char bits_per_pixel;
        bool png;
        uint32_t captures;
        uint32_t wait_milliseconds;
    } s_Translation;
#pragma pack()

    /**
      * This function captures screenshot according to a validated bytes array.
      * @param byte_array - the validated byte array
      * @param connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    bool ExecuteTranslatedByteArray(s_Translation *byte_array,
                                    networking::ITCPClient& connection);

    /**
      * This function captures a single screen shot and sends it to the client.
      * @param byte_array - the validated byte array
      * @param connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    bool CaptureAndSend(s_Translation *byte_array,
                        networking::ITCPClient& connection);

    /**
      * This function captures a single screen shot and sends it to the client
      * in BMP format.
      * @param screenshot - the screen shot in BMP format.
      * @param connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    bool SendAsBMP(methods::screenshot::BmpScreenshot& screenshot,
                   networking::ITCPClient& connection);

    /**
      * This function captures a single screen shot and sends it to the client
      * in PNG format.
      * @param screenshot - the screen shot in BMP format.
      * @param connection - a TCP client to communicate with remote control.
      * @return If an error occurs, false is returned.
      *         Otherwise, true is returned.
      */
    bool SendAsPNG(methods::screenshot::BmpScreenshot& screenshot,
                   networking::ITCPClient& connection);

};
}
