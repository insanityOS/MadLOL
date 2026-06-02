/*! @file AxLOL_types.h
 *  @brief AxLOL Base type definitions.
 *
 * Definitions for AxLOL basic types, including status returns.
 */

#ifndef AXLOL_TYPES_H
#define AXLOL_TYPES_H

#include <stdint.h>

/*! @brief Status enumeration definition.
 *
 * Enumeration for AxLOL Status returns. For variable declaration, please use @ref AxLOL_Status_t instead; this
 * definition is intended for value definitions.
 *
 * Operates in a bitwise fashion as faults are not mutually exclusive.
 *
 *  @var AxLOL_Status_e::LOL_SUCCESS
 * Operation reports successfully. See specific functions for further details.
 *
 *  @var AxLOL_Status_e::LOL_NULLPTR
 * Operation failed due to an unexpected null pointer.
 *
 *  @var AxLOL_Status_e::LOL_BADPARAM
 * Operation failed because of a parameter sanitization failure. See specific function for details as to what this
 * means.
 *
 *  @var AxLOL_Status_e::LOL_INNERFAIL
 * Internal function call failed. See accompanying fault for more details.
 *
 *  @var AxLOL_Status_e::LOL_BADBOUNDS
 * Operation failed as the requested operation exists entirely out of bounds for the given frame buffer.
 *
 *  @var AxLOL_Status_e::LOL_BADCHAR
 * Operation failed as the character provided is not an ASCII character.
 */
typedef enum {
  LOL_SUCCESS = 0x0000,
  LOL_NULLPTR = 0x0001,
  LOL_BADPARAM = 0x0002,
  LOL_INNERFAIL = 0x0004,
  LOL_BADBOUNDS = 0x0008,
  LOL_BADCHAR = 0x0010,
} AxLOL_Status_e;

/*! @brief Status type definition.
 *
 * Type for AxLOL Status returns. Would that C23 were more widespread.
 *
 * For actual values of this type, see the enumeration @ref AxLOL_Status_e.
 */
typedef uint16_t AxLOL_Status_t;

/*! @brief Size definition.
 *
 * Definition of a Size in AxLOL library. This is intended to be used for defining the absolute size of patterns and
 * buffers. For defining locations in a FrameBuffer or Pattern, see @ref AxLOL_Coord.
 *
 *  @var AxLOL_Size::width
 * Width of the specified object in pixels.
 *
 *  @var AxLOL_Size::height
 * Height of the specified object in pixels.
 */
typedef struct {
  uint32_t width;
  uint32_t height;
} AxLOL_Size;

/*! @brief Coordinate definition.
 *
 *  @var AxLOL_Coord::x
 * X coordinate for the specified point (X pixels to the right of the origin)
 *
 *  @var AxLOL_Coord::y
 * Y coordinate for the specified point (Y pixels above the origin)
 */
typedef struct {
  int32_t x;
  int32_t y;
} AxLOL_Coord;

#endif
