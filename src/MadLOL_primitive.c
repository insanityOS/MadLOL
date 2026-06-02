#include "MadLOL_primitive.h"
#include <stdbool.h>
#include "MadLOL_frame_buffer.h"
#include "MadLOL_types.h"

static MadLOL_Pixel* getPixel(MadLOL_FrameBuffer fb, MadLOL_Coord coord) {
  return &(fb.frame[coord.y * fb.size.width + coord.x]);
}

static bool areBoundsSane(MadLOL_FrameBuffer fb, MadLOL_Coord coord, MadLOL_Size size) {
  if (coord.x >= (int32_t)fb.size.width || coord.x + (int32_t)size.width <= 0)
    return false;

  if (coord.y >= (int32_t)fb.size.height || coord.y + (int32_t)size.height <= 0)
    return false;

  return true;
}

static bool shouldExpressPixel(int32_t i,
                               int32_t j,
                               MadLOL_Pattern pattern,
                               MadLOL_FrameBuffer fb,
                               MadLOL_Coord coord) {
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

MadLOL_Status_t MadLOL_applyPattern(MadLOL_FrameBuffer fb,
                                    MadLOL_Pattern pattern,
                                    MadLOL_Coord coord,
                                    MadLOL_Color color) {
  if ((!fb.frame) || (!pattern.bitmap))
    return LOL_NULLPTR;

  if (!areBoundsSane(fb, coord, pattern.size))
    return LOL_BADBOUNDS;

  if ((pattern.size.width == 0) || (pattern.size.height == 0))
    return LOL_BADPARAM;

  MadLOL_Status_t setColor_status = LOL_SUCCESS;

  for (int32_t j = 0; j < pattern.size.height; j++) {
    for (int32_t i = 0; i < pattern.size.width; i++) {
      MadLOL_Coord targetCoord = {.x = i + coord.x, .y = j + coord.y};

      if (shouldExpressPixel(i, j, pattern, fb, targetCoord)) {
        MadLOL_Pixel* targetPixel = getPixel(fb, targetCoord);
        setColor_status = MadLOL_setColor(targetPixel, color);
      }

      if (setColor_status != LOL_SUCCESS)
        return setColor_status | LOL_INNERFAIL;
    }
  }

  return setColor_status;
}

MadLOL_Status_t MadLOL_fillBlock(MadLOL_FrameBuffer fb, MadLOL_Size size, MadLOL_Coord coord, MadLOL_Color color) {
  if (!fb.frame)
    return LOL_NULLPTR;

  if (!areBoundsSane(fb, coord, size))
    return LOL_BADBOUNDS;

  MadLOL_Status_t setColor_status = LOL_SUCCESS;

  for (int32_t i = coord.y; i < (int32_t)size.height + coord.y; i++) {
    if ((i >= 0) && i < (int32_t)fb.size.height) {
      for (int32_t j = coord.x; j < (int32_t)size.width + coord.x; j++) {
        if ((j >= 0) && (j < (int32_t)fb.size.width)) {
          MadLOL_Coord targetCoord = {.x = j, .y = i};
          MadLOL_Pixel* targetPixel = getPixel(fb, targetCoord);
          setColor_status = MadLOL_setColor(targetPixel, color);
        }
        if (setColor_status != LOL_SUCCESS)
          return setColor_status | LOL_INNERFAIL;
      }
    }
  }

  return LOL_SUCCESS;
}

MadLOL_Status_t MadLOL_paintBuffer(MadLOL_FrameBuffer fb, MadLOL_Color color) {
  return MadLOL_fillBlock(fb, fb.size, (MadLOL_Coord){.x = 0, .y = 0}, color);
}
