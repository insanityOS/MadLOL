/*! @file AxLOL_string.h
 *  @brief AxLOL string operations and definitions.
 *
 * Definitions for AxLOL string operations. Primarily printing of strings. Note that only fixed-width strings are
 * supported.
 */

#ifndef AXLOL_STRING_H
#define AXLOL_STRING_H

#include "AxLOL_char.h"

/*! @brief String definition for AxLOL.
 *
 * String definition for AxLOL. Strings must be fixed-width; null termination is ignored.
 *
 *  @var AxLOL_String::len
 * Length of the string in characters.
 *
 *  @var AxLOL_String::str
 * Pointer to actual string; must be at least of size @c len or out-of-bounds reads will occur.
 */
typedef struct {
  int32_t len;
  char* str;
} AxLOL_String;

/*! @brief Print a string.
 *
 * Prints a string into the buffer at the specified coordinate. At least part of the string must be within the bounds
 * of the frame buffer, or this operation will fail with @ref LOL_BADBOUNDS. Standard null checks are applied to both
 * the frame buffer and the string. String length must be at least 1 or this operation will fail with @ref LOL_BADPARAM.
 * If the string contains an invalid character (i.e. non-ASCII), this operation will fail with @ref LOL_BADCHAR upon
 * reaching the character (which can result in a partial print). ASCII control characters are treated as regular
 * printable characters without regard to their normal control functionality.
 * Uses the current active font map as set by @ref AxLOL_setFont().
 *
 *  @param fb: Frame Buffer to write into.
 *  @parma str: String to write into frame buffer.
 *  @param coord: Bottom leftmost pixel in the string block to write.
 *  @param color: Color to draw string as.
 *  @returns Returns @ref LOL_SUCCESS if successful, and an appropriate failure mode otherwise.
 */
AxLOL_Status_t AxLOL_printString(AxLOL_FrameBuffer fb, AxLOL_String str, AxLOL_Coord coord, AxLOL_Color color);

#endif
