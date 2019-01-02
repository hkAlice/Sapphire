#ifndef _FONTDATA
#define _FONTDATA

namespace Sapphire::GUI
{
  struct FontData
  {
    unsigned char* pixels;
    int width;
    int height;
    int bpp;
  };
}

#endif