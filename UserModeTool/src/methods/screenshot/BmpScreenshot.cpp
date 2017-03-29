#include "methods/screenshot/BmpScreenshot.h"

#include <windows.h>

#include "methods/screenshot/StaticFunctions.h"
#include <iostream>


using namespace methods::screenshot;

BmpScreenshot::BmpScreenshot(WORD bits_per_pixel)
{
    GetVirtualScreenRectangle(&m_upperLeftX,
                              &m_upperLeftY,
                              &m_width,
                              &m_height);
    CreateFileHeader();
    CreateBMIHeader(bits_per_pixel);
    CaptureScreenshot();
}

BmpScreenshot::~BmpScreenshot()
{
    DeleteObject(m_bitmap);
}

BITMAPFILEHEADER const*
BmpScreenshot::GetFileHeader(size_t *size)
const
{
    *size = sizeof(m_fileHeader);

    return ( &m_fileHeader );
}

BITMAPINFOHEADER const*
BmpScreenshot::GetBMIHeader(size_t *size)
const
{
    *size = sizeof(m_infoHeader);

    return ( &m_infoHeader );
}

BYTE*
BmpScreenshot::GetPixelData(size_t *size)
{
    *size = m_pixelData_Len;

    return ( m_pixelData );
}

uint32_t
BmpScreenshot::BitsPerPixel()
const
{
    return ( m_infoHeader.biBitCount );
}

uint32_t
BmpScreenshot::Width()
const
{
    return ( m_width );
}

uint32_t
BmpScreenshot::Height()
const
{
    return ( m_height );
}

/* private */

void
BmpScreenshot::CreateFileHeader()
{
    m_fileHeader.bfType      = 0x4d42;
    m_fileHeader.bfSize      = 0;
    m_fileHeader.bfReserved1 = 0;
    m_fileHeader.bfReserved2 = 0;
    m_fileHeader.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
}

void
BmpScreenshot::CreateBMIHeader(WORD bits_per_pixel)
{
    m_infoHeader.biSize          = sizeof(m_infoHeader);
    m_infoHeader.biWidth         = m_width;
    m_infoHeader.biHeight        = -m_height;
    m_infoHeader.biPlanes        = 1;
    m_infoHeader.biBitCount      = bits_per_pixel;
    m_infoHeader.biCompression   = BI_RGB;
    m_infoHeader.biSizeImage     = 0;
    m_infoHeader.biXPelsPerMeter = 0;
    m_infoHeader.biYPelsPerMeter = 0;
    m_infoHeader.biClrUsed       = 0;
    m_infoHeader.biClrImportant  = 0;
}

void
BmpScreenshot::CaptureScreenshot()
{
    HDC hScreenDC = GetDC(0);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    m_bmiInfo.bmiHeader = m_infoHeader;

    m_bitmap = CreateDIBSection(hScreenDC, &m_bmiInfo, DIB_RGB_COLORS, (void**)&m_pixelData, 0, 0);
    SelectObject(hMemoryDC, m_bitmap);
    BitBlt(hMemoryDC, 0, 0, m_width, m_height, hScreenDC, m_upperLeftX, m_upperLeftY, SRCCOPY);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    // save dibsection data
    m_pixelData_Len = (((m_infoHeader.biBitCount*m_width + 31) & (~31))/8)*m_height;
}
