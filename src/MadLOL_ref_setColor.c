#define MADLOL_CREATE_REFERENCE_PIXEL
#include "MadLOL_frame_buffer.h"

MadLOL_Status_t MadLOL_setColor(MadLOL_Pixel* pixel, MadLOL_Color color) {
  if (!pixel)
    return LOL_NULLPTR;

  pixel->color = color;

  return LOL_SUCCESS;
}
