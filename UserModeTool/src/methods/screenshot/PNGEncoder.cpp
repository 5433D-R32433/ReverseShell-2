#include "methods/screenshot/PNGEncoder.h"
#include "methods/screenshot/BmpScreenshot.h"
#include "methods/screenshot/lodepng.h"


using namespace methods::screenshot;

PNGEncoder::PNGEncoder(
    BmpScreenshot& screenshot)
{
    switch( screenshot.BitsPerPixel() )
    {
    case 24:
        Encode24(screenshot);

        break;

    case 32:
        Encode32(screenshot);

        break;

    default:
        m_encodedData = nullptr;
        m_encodedData_Len = 0;

        break;
    }
}

PNGEncoder::~PNGEncoder()
{
    free(m_encodedData);
}

unsigned char const*
PNGEncoder::GetData(size_t *size)
const
{
    *size = m_encodedData_Len;

    return ( m_encodedData );
}

void
PNGEncoder::Encode24(
    BmpScreenshot& screenshot)
{
    size_t size;

    char *bmp_pixel_data = (char*)screenshot.GetPixelData(&size);

    // convert memory from bgr format to rgb
    for ( unsigned i = 0; i< size-2; i+=3)
    {
        int tmp = bmp_pixel_data[i+2];
        bmp_pixel_data[i+2] = bmp_pixel_data[i];
        bmp_pixel_data[i] = tmp;
    }

    int error = lodepng_encode24(&m_encodedData,
                                 &m_encodedData_Len,
                                 screenshot.GetPixelData(&size),
                                 screenshot.Width(),
                                 screenshot.Height());

    if ( 0 != error )
    {
        m_encodedData = nullptr;
        m_encodedData_Len = 0;
    }
}

void
PNGEncoder::Encode32(
    BmpScreenshot& screenshot)
{
    size_t size;

    char *bmp_pixel_data = (char*)screenshot.GetPixelData(&size);

    // convert memory from bgr format to rgb
    for ( unsigned i = 0; i< size-3; i+=4)
    {
        int tmp = bmp_pixel_data[i+2];
        bmp_pixel_data[i+2] = bmp_pixel_data[i];
        bmp_pixel_data[i] = tmp;
    }

    int error = lodepng_encode32(&m_encodedData,
                                 &m_encodedData_Len,
                                 screenshot.GetPixelData(&size),
                                 screenshot.Width(),
                                 screenshot.Height());

    if ( 0 != error )
    {
        m_encodedData = nullptr;
        m_encodedData_Len = 0;
    }
}
