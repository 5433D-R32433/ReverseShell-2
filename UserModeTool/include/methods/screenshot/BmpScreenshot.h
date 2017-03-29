#pragma once

#include <cstdint>
#include <windows.h>


namespace methods
{
namespace screenshot
{
/**
  * Class creates a screen shot of the virtual screen.
  * Users of this class should set DPI awareness before creating an instance
  * so that the whole virtual screen will be captured.
  *
  * A screen shot is taken on instance creation (this is implemented inside
  * the constructor).
  */
class BmpScreenshot
{
public:

    BmpScreenshot(WORD bits_per_pixel);
    virtual ~BmpScreenshot();

    /**
      * Use this function to get the header for a BMP file to save this screen shot to.
      * @param[out] size - size of m_fileHeader
      * @return a pointer to m_fileHeader.
      */
    BITMAPFILEHEADER const* GetFileHeader(size_t *size) const;

    /**
      * Use this function to get the BMP info header
      * for a BMP file to save this screen shot to.
      * @param[out] size - size of m_infoHeader
      * @return a pointer to m_infoHeader.
      */
    BITMAPINFOHEADER const* GetBMIHeader(size_t *size) const;

    /**
      * Use this function to get the pixel data of this screen shot.
      * @param[out] size - m_pixelData_Len
      * @return m_pixelData.
      */
    BYTE* GetPixelData(size_t *size);

    /**
      * Use this function to get the number of bits per pixel in screen shot.
      * @return number of bits per pixel in screen shot.
      */
    uint32_t BitsPerPixel() const;

    /**
      * Get the width in pixels of the screen shot
      * @return width of screen shot in pixels
      */
    uint32_t Width() const;

    /**
      * Get the height in pixels of the screen shot
      * @return height of screen shot in pixels
      */
    uint32_t Height() const;


private:

    BITMAPFILEHEADER m_fileHeader;
    BITMAPINFOHEADER m_infoHeader;
    BITMAPINFO m_bmiInfo;
    HBITMAP m_bitmap;
    BYTE *m_pixelData;
    int m_pixelData_Len;

    /**
      * Virtual screen size details.
      */
    uint32_t m_upperLeftX,
             m_upperLeftY,
             m_width,
             m_height;

    /**
      * Function initializes m_fileHeader;
      */
    void CreateFileHeader();

    /**
      * Function initializes m_infoHeader;
      * @param[in] bits_per_pixel - number of bits per pixel.
      */
    void CreateBMIHeader(WORD bits_per_pixel);

    /**
      * Function creates a screen shot and stores the pixel data in m_pixelData.
      */
    void CaptureScreenshot();
};
}
}
