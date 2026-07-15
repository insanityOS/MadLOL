#include "MadLOL_transform_buffer.h"
#include "MadLOL_frame_buffer.h"
#include "MadLOL_types.h"

static inline MadLOL_Status_t rotateBuffer_copy_sanitizeParameters(const MadLOL_FrameBuffer fb_src,
                                                                   MadLOL_FrameBuffer fb_dst,
                                                                   MadLOL_Rotate_t rotation);
static inline MadLOL_Status_t rotateBuffer_copy_90(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst);
static inline MadLOL_Status_t rotateBuffer_copy_180(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst);
static inline MadLOL_Status_t rotateBuffer_copy_270(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst);

MadLOL_Status_t MadLOL_rotateBuffer_copy(const MadLOL_FrameBuffer fb_src,
                                         MadLOL_FrameBuffer fb_dst,
                                         MadLOL_Rotate_t rotation) {
  MadLOL_Status_t status = rotateBuffer_copy_sanitizeParameters(fb_src, fb_dst, rotation);

  if (LOL_SUCCESS != status)
    return status;

  switch (rotation) {
    case LOL_DEGREES_90:
      return rotateBuffer_copy_90(fb_src, fb_dst);
    case LOL_DEGREES_180:
      return rotateBuffer_copy_180(fb_src, fb_dst);
    default:
      return rotateBuffer_copy_270(fb_src, fb_dst);
  }
}

static inline MadLOL_Status_t rotateBuffer_copy_sanitizeParameters(const MadLOL_FrameBuffer fb_src,
                                                                   MadLOL_FrameBuffer fb_dst,
                                                                   MadLOL_Rotate_t rotation) {
  if (!fb_src.frame || !fb_dst.frame)
    return LOL_NULLPTR;

  if ((0 == fb_src.size.height) || (0 == fb_src.size.width))
    return LOL_BADBOUNDS;

  if ((rotation > LOL_DEGREES_270) || (0 == rotation))
    return LOL_BADPARAM;

  if (LOL_DEGREES_180 == rotation) {
    if (fb_src.size.width != fb_dst.size.width)
      return LOL_BADBOUNDS;
    if (fb_src.size.height != fb_dst.size.height)
      return LOL_BADBOUNDS;
  } else {
    if (fb_src.size.width != fb_dst.size.height)
      return LOL_BADBOUNDS;
    if (fb_src.size.height != fb_dst.size.width)
      return LOL_BADBOUNDS;
  }

  return LOL_SUCCESS;
}

static inline MadLOL_Status_t rotateBuffer_copy_90(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst) {
  MadLOL_Status_t status = LOL_SUCCESS;
  for (uint16_t x_src = 0; x_src < fb_src.size.width; x_src++) {
    for (uint16_t y_src = 0; y_src < fb_src.size.height; y_src++) {
      uint16_t x_dst = fb_dst.size.width - y_src - 1;
      uint16_t y_dst = x_src;
      status = MadLOL_setColor(&fb_dst.frame[y_dst * fb_dst.size.width + x_dst],
                               fb_src.frame[y_src * fb_src.size.width + x_src].color);

      if (status != LOL_SUCCESS)
        return status | LOL_INNERFAIL;
    }
  }

  return status;
}

static inline MadLOL_Status_t rotateBuffer_copy_180(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst) {
  MadLOL_Status_t status = LOL_SUCCESS;
  for (uint16_t x_src = 0; x_src < fb_src.size.width; x_src++) {
    for (uint16_t y_src = 0; y_src < fb_src.size.height; y_src++) {
      uint16_t x_dst = fb_dst.size.width - x_src - 1;
      uint16_t y_dst = fb_dst.size.height - y_src - 1;
      status = MadLOL_setColor(&fb_dst.frame[y_dst * fb_dst.size.width + x_dst],
                               fb_src.frame[y_src * fb_src.size.width + x_src].color);

      if (status != LOL_SUCCESS)
        return status | LOL_INNERFAIL;
    }
  }

  return status;
}

static inline MadLOL_Status_t rotateBuffer_copy_270(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst) {
  MadLOL_Status_t status = LOL_SUCCESS;
  for (uint16_t x_src = 0; x_src < fb_src.size.width; x_src++) {
    for (uint16_t y_src = 0; y_src < fb_src.size.height; y_src++) {
      uint16_t x_dst = y_src;
      uint16_t y_dst = fb_dst.size.height - x_src - 1;
      status = MadLOL_setColor(&fb_dst.frame[y_dst * fb_dst.size.width + x_dst],
                               fb_src.frame[y_src * fb_src.size.width + x_src].color);

      if (status != LOL_SUCCESS)
        return status | LOL_INNERFAIL;
    }
  }

  return status;
}
