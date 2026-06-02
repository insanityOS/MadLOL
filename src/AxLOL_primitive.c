#include "AxLOL_primitive.h"
#include <stdbool.h>
#include "AxLOL_frame_buffer.h"
#include "AxLOL_types.h"

static AxLOL_Pixel* getPixel(AxLOL_FrameBuffer fb, AxLOL_Coord coord) {
  return &(fb.frame[coord.y * fb.size.width + coord.x]);
}

static bool areBoundsSane(AxLOL_FrameBuffer fb, AxLOL_Coord coord, AxLOL_Size size) {
  if (coord.x >= (int32_t)fb.size.width || coord.x + (int32_t)size.width <= 0)
    return false;

  if (coord.y >= (int32_t)fb.size.height || coord.y + (int32_t)size.height <= 0)
    return false;

  return true;
}

static bool shouldExpressPixel(int32_t i, int32_t j, AxLOL_Pattern pattern, AxLOL_FrameBuffer fb, AxLOL_Coord coord) {
  if ((coord.x < 0) || (coord.x >= fb.size.width))
    return false;
  if ((coord.y < 0) || (coord.y >= fb.size.height))
    return false;

  int32_t width_bytes = ((pattern.size.width - 1) / 8) + 1;
  int32_t widthByteNumber = i / 8;

  // ##### Fuck me dead, I can't figure this out.
  uint8_t bitmap_byte = pattern.bitmap[width_bytes * (pattern.size.height - j - 1) + widthByteNumber];

  return (bitmap_byte & (0x80 >> i % 8));
}

AxLOL_Status_t AxLOL_applyPattern(AxLOL_FrameBuffer fb, AxLOL_Pattern pattern, AxLOL_Coord coord, AxLOL_Color color) {
  if ((!fb.frame) || (!pattern.bitmap))
    return LOL_NULLPTR;

  if (!areBoundsSane(fb, coord, pattern.size))
    return LOL_BADPARAM;

  if ((pattern.size.width == 0) || (pattern.size.height == 0))
    return LOL_BADPARAM;

  AxLOL_Status_t setColor_status = LOL_SUCCESS;

  for (int32_t j = 0; j < pattern.size.height; j++) {
    for (int32_t i = 0; i < pattern.size.width; i++) {
      AxLOL_Coord targetCoord = {.x = i + coord.x, .y = j + coord.y};

      if (shouldExpressPixel(i, j, pattern, fb, targetCoord)) {
        AxLOL_Pixel* targetPixel = getPixel(fb, targetCoord);
        setColor_status = AxLOL_setColor(targetPixel, color);
      }

      if (setColor_status != LOL_SUCCESS)
        return setColor_status | LOL_INNERFAIL;
    }
  }

  return setColor_status;
}

AxLOL_Status_t AxLOL_fillBlock(AxLOL_FrameBuffer fb, AxLOL_Size size, AxLOL_Coord coord, AxLOL_Color color) {
  if (!fb.frame)
    return LOL_NULLPTR;

  if (!areBoundsSane(fb, coord, size))
    return LOL_BADPARAM;

  AxLOL_Status_t setColor_status = LOL_SUCCESS;

  for (int32_t i = coord.y; i < (int32_t)size.height + coord.y; i++) {
    if ((i >= 0) && i < (int32_t)fb.size.height) {
      for (int32_t j = coord.x; j < (int32_t)size.width + coord.x; j++) {
        if ((j >= 0) && (j < (int32_t)fb.size.width)) {
          AxLOL_Coord targetCoord = {.x = j, .y = i};
          AxLOL_Pixel* targetPixel = getPixel(fb, targetCoord);
          setColor_status = AxLOL_setColor(targetPixel, color);
        }
        if (setColor_status != LOL_SUCCESS)
          return setColor_status | LOL_INNERFAIL;
      }
    }
  }

  return LOL_SUCCESS;
}

AxLOL_Status_t AxLOL_paintBuffer(AxLOL_FrameBuffer fb, AxLOL_Color color) {
  return AxLOL_fillBlock(fb, fb.size, (AxLOL_Coord){.x = 0, .y = 0}, color);
}
