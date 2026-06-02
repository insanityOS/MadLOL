/*! @file AxLOL_frame_buffer.h
 *  @brief FrameBuffer type definitions
 *
 * Definition for Frame Buffer type.
 */

#ifndef AXLOL_FRAME_BUFFER_H
#define AXLOL_FRAME_BUFFER_H

#include "AxLOL_types.h"

#define AXLOL_CREATE_REFERENCE_PIXEL

#ifdef AXLOL_CREATE_REFERENCE_PIXEL

/*! @brief Reference color definition.
 *
 * Reference color definition upon which this library is tested. 5-6-5 format is selected as it represents an unusual
 * case, and seems like a reasonable challenge to the author of this library.
 *
 *  @var AxLOL_Color::R
 * Red channel definition
 *
 *  @var AxLOL_Color::G
 * Green channel definition
 *
 *  @var AxLOL_Color:B
 * Blue channel definition
 */
typedef struct __attribute__((__packed__)) {
  uint8_t R : 5;
  uint8_t G : 6;
  uint8_t B : 5;
} AxLOL_Color;

/*! @brief Reference pixel definition.
 *
 * Reference implementation for the pixels upon which the library operates.
 * This does not support transparency.
 *
 *  @var AxLOL_Pixel::color
 * Color of the current pixel.
 */
typedef struct {
  AxLOL_Color color;
} AxLOL_Pixel;

#else
#include "AxLOL_pixel.h"
#endif

/*! @brief Frame Buffer type definition.
 *
 * Type definition for a fully-fledged FrameBuffer in the AxLOL library. Note that the frame must be a
 * properly-allocated pixel array of size `size.width * size.height`.
 *
 *  @warning Other than checks for NULL, this struct will assume you have correctly allocated the frame.
 *
 *  @var AxLOL_FrameBuffer::size
 * Size of the FrameBuffer
 *
 *  @var AxLOL_FrameBuffer::frame
 * Pointer to array of AxLOL Pixels of @c width by @c height. This must be a standard, 1-dimensional array to preserve
 * contiguity in memory.
 */
typedef struct {
  AxLOL_Size size;
  AxLOL_Pixel* frame;
} AxLOL_FrameBuffer;

/*! @brief Declaration for fundamental color application function.
 *
 * Declaration for the base color application function. Must be defined by the user if the reference pixel
 * implementation is not used.
 *
 * For the reference implementation, this is a simple copy operation. Extended implementations may implement
 * transparency via clever math that the library author is too lazy to implement and test.
 *
 * Note that the following is true for the reference implementation; for return type, calling functions only check for
 * @ref LOL_SUCCESS.
 *
 *  @param pixel: Pointer to the individual pixel upon which to apply the @c color.
 *  @param color: Color to apply to the @c pixel.
 *  @returns Returns @ref LOL_SUCCESS if operation succeeded, @ref LOL_NULLPTR if @c pixel was a null pointer.
 */
AxLOL_Status_t AxLOL_setColor(AxLOL_Pixel* pixel, AxLOL_Color color);

#endif
