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
 * Pattern type definition. The bitmap must be defined as a 2D array of size [ceil(size.width/8)] by [size.height] in
 * which each @ref AxLOL_Pixel is a single bit in the pattern. In other words, the size is the size in individual
 * pixels. The Patterns are defined by the top row first, building downwards. As an example, the literal:
 *
 * {{0x18},{0x3C},{0x66},{0x66},{0x7E},{0x66},{0x66},{0x00}}
 *
 * which represents the letter 'A', is rendered like so:
 *
 *       76543210
 * 0x18 7   XX   7
 * 0x3C 6  XXXX  6
 * 0x66 5 XX  XX 5
 * 0x66 4 XX  XX 4
 * 0x7E 3 XXXXXX 3
 * 0x66 2 XX  XX 2
 * 0x66 1 XX  XX 1
 * 0x00 0        0
 *       76543210
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
 *  2. No part of the @c pattern exists within the Frame Buffer for the given @c coord (@ref LOL_BADBOUNDS)
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
 * Bad returns can be generated under the following circumstances:
 *  1. A null pointer is passed in either @c fb or @c pattern (@ref LOL_NULLPTR)
 *  2. No part of the @c size exists within the Frame Buffer for the given @c coord (@ref LOL_BADBOUNDS)
 *  3. Any inner function call returns a non-success status (@ref LOL_INNERFAIL). Non-success status is also sent.
 *
 *  @param fb: Frame buffer to fill with block.
 *  @param size: Size of the block to fill.
 *  @param coord: Where to place the block.
 *  @param color: Color to paint the block.
 *  @returns Returns @ref LOL_SUCCESS
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
