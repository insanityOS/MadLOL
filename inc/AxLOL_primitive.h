/*! @file AxLOL_primitive.h
 *  @brief AxLOL primitive operations.
 *
 * Definitions for fundamental AxLOL operations, such as blanking a Frame Buffer, setting solid colors in a block, and
 * applying bit patterns.
 */

#ifndef AXLOL_PRIMITIVE_H
#define AXLOL_PRIMITIVE_H

#include "AxLOL_frame_buffer.h"
#include "AxLOL_types.h"

/*! @brief Pattern type definition.
 *
 * Pattern type definition. The bitmap must be defined as a 2D array of size [size.width/8] by [size.height/8] in which
 * each @ref AxLOL_Pixel is a single bit in the pattern. If @c size.width is not a multiple of 8, the unused bits in the
 * final byte in each row are wasted.
 *
 *  @var AxLOL_Pattern::size
 * Size of the pattern in Pixels.
 *
 *  @var AxLOL_Pattern::bitmap
 * Pointer to the 2D bit array in memory.
 */
typedef struct {
  AxLOL_Size size;
  uint8_t* bitmap;
} AxLOL_Pattern;

/*! @brief Apply Pattern into the Frame Buffer.
 *
 * Applies the pattern into the Frame Buffer with the selected color.
 *
 * Bad returns can be generated under the following circumstances:
 *  1. A null pointer is passed in either @c fb or @c pattern (@ref LOL_NULLPTR)
 *  2. No part of the @c pattern exists within the Frame Buffer for the given @c coord (@ref LOL_BADPARAM)
 *  3. Any inner function call returns a non-success status (@ref LOL_INNERFAIL). Non-success status is also sent.
 *
 *  @param fb: Frame buffer in which to apply pattern.
 *  @param pattern: Pattern to apply.
 *  @param coord: Where to apply bottom leftmost pixel.
 *  @param color: Color to apply on pattern.
 *  @returns Returns @ref LOL_SUCCESS if operation completed successfully, relevant failure status otherwise.
 */
AxLOL_Status_t AxLOL_applyPattern(AxLOL_FrameBuffer fb, AxLOL_Pattern pattern, AxLOL_Coord coord, AxLOL_Color color);

/*! @brief Fill a block in the Frame Buffer with the specified color.
 *
 * Places a block of the given color into the Frame Buffer.
 *
 *  @param fb: Frame buffer to fill with block.
 *  @param size: Size of the block to fill.
 *  @param coord: Where to place the block.
 *  @param color: Color to paint the block.
 *  @returns Returns @ref LOL_NULLPTR if @c fb contains a null pointer, @ref LOL_SUCCESS otherwise. May return @ref
 *  LOL_INNERFAIL if call to @ref AxLOL_setColor() fails.
 *  @post @c fb is completely painted @c color.
 */
AxLOL_Status_t AxLOL_fillBlock(AxLOL_FrameBuffer fb, AxLOL_Size size, AxLOL_Coord coord, AxLOL_Color color);

/*! @brief Fill the Frame Buffer with the specified color.
 *
 * Fills the Frame Buffer with the given color. Useful for blanking a frame buffer.
 *
 *  @param fb: Frame buffer to paint.
 *  @param color: Color to paint @c fb.
 *  @returns Returns @ref LOL_NULLPTR if @c fb contains a null pointer, @ref LOL_SUCCESS otherwise. May return @ref
 *  LOL_INNERFAIL if call to @ref AxLOL_setColor() fails.
 *  @post @c fb is completely painted @c color.
 */
AxLOL_Status_t AxLOL_paintBuffer(AxLOL_FrameBuffer fb, AxLOL_Color color);

#endif
