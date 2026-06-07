/*! @file MadLOL_transform_buffer.h
 *  @brief Translation declarations
 *
 * Declarations for frame buffer translation functions.
 */

#ifndef MADLOL_TRANSFORM_BUFFER_H
#define MADLOL_TRANSFORM_BUFFER_H

#include <stdint.h>
#include "MadLOL_types.h"
#include "MadLOL_frame_buffer.h"

/*! @brief Rotation selection enumeration.
 *
 * Selection enumeration for how to rotate a frame buffer. For variable declarations, see @ref MaxLOL_Rotate_t instead.
 *
 *  @var MadLOL_Rotate_e::LOL_DEGREES_90
 * Rotation operation will rotate 90 degrees counterclockwise.
 *
 *  @var MadLOL_Rotate_e::LOL_DEGREES_180
 * Rotation operation will rotate 180 degrees counterclockwise.
 *
 *  @var MadLOL_Rotate_e::LOL_DEGREES_270
 * Rotation operation will rotate 270 degrees counterclockwise.
 */
typedef enum {
  LOL_DEGREES_90 = 1,
  LOL_DEGREES_180 = 2,
  LOL_DEGREES_270 = 3,
} MadLOL_Rotate_e;

/*! @brief Rotation selection type.
 *
 * Type for rotation selection parameters. For enumerated values, see @ref MadLOL_Rotate_e.
 */
typedef uint16_t MadLOL_Rotate_t;

/*! @brief Copy and rotate one frame buffer into another.
 *
 * Copies one frame buffer into another frame buffer while rotating the pixels by 90, 180, or 270 degrees
 * counterclockwise. The destination buffer must be properly allocated according to the size of the source buffer; if
 * the source buffer is of @c x width and @c y height, the destination buffer must be of @c y width and @c height. Both
 * the source and destination frame buffers must have adequate space in their internal array; this is not checked. If
 * either frame buffer contains a null pointer, this function returns @ref MadLOL_Status_e::LOL_NULLPTR. If the size of
 * the destination frame buffer (or if the source buffer size field is obviously erroneous, this function returns @ref
 * MadLOL_Status_e::LOL_BADPARAM.
 *
 *  @param fb_src: Source frame buffer from which to copy/rotate.
 *  @param fb_dst: Destination frame buffer into which to paste rotated image.
 *  @param rotation: Rotation amount selection.
 *  @returns Returns @ref MadLOL_Status_e::LOL_SUCCESS if successful, relevant failure otherwise.
 *  @post Contents of @c fb_src are rotated into @c fb_dst.
 */
MadLOL_Status_t MadLOL_rotateBuffer_copy(const MadLOL_FrameBuffer fb_src, MadLOL_FrameBuffer fb_dst, MadLOL_Rotate_t rotation);
#endif
