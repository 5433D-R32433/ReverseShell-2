#pragma once

#include "methods/screenshot/BmpScreenshot.h"


namespace methods
{
namespace screenshot
{
/**
  * This class encodes instances of methods::screenshot::BmpScreenShot to PNG.
  * Can only encode BMPs of 24 or 32 bits per pixel.
  * The pointer to data will contain nullptr in other cases.
  */
class PNGEncoder
{
public:
    PNGEncoder(methods::screenshot::BmpScreenshot& screenshot);
    virtual ~PNGEncoder();

    /**
      * Use this function to get the encoded data.
      * @param[out] size - length of encoded data array.
      * @return If the constructor successfully encoded a 24 or 32 bits per pixel BMP,
      *         a pointer to the encoded data array is returned.
      *         Otherwise, nullptr is returned.
      */
    unsigned char const* GetData(size_t *size) const;

protected:

    unsigned char *m_encodedData;
	size_t m_encodedData_Len;

    /**
      * Function encodes 24-bits-per-pixel BMPs.
      * @param[in] screenshot - a BMP screen shot object with data to encode.
      */
    void Encode24(BmpScreenshot& screenshot);

    /**
      * Function encodes 32-bits-per-pixel BMPs.
      * @param[in] screenshot - a BMP screen shot object with data to encode.
      */
    void Encode32(BmpScreenshot& screenshot);

};
}
}
