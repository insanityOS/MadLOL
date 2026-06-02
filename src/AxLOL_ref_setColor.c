#define AXLOL_CREATE_REFERENCE_PIXEL
#include "AxLOL_frame_buffer.h"

AxLOL_Status_t AxLOL_setColor(AxLOL_Pixel* pixel, AxLOL_Color color) {
  if (!pixel)
    return LOL_NULLPTR;

  pixel->color = color;

  return LOL_SUCCESS;
}
