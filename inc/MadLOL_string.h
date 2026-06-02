/*! @file MadLOL_string.h
 *  @brief MadLOL string operations and definitions.
 *
 * Definitions for MadLOL string operations. Primarily printing of strings. Note that only fixed-width strings are
 * supported.
 */

#ifndef MADLOL_STRING_H
#define MADLOL_STRING_H

#include "MadLOL_char.h"

/*! @brief String definition for MadLOL.
 *
 * String definition for MadLOL. Strings must be fixed-width; null termination is ignored.
 *
 *  @var MadLOL_String::len
 * Length of the string in characters.
 *
 *  @var MadLOL_String::str
 * Pointer to actual string; must be at least of size @c len or out-of-bounds reads will occur.
 */
typedef struct {
  int32_t len;
  char* str;
} MadLOL_String;

/*! @brief Print a string.
 *
 * Prints a string into the buffer at the specified coordinate. At least part of the string must be within the bounds
 * of the frame buffer, or this operation will fail with @ref LOL_BADBOUNDS. Standard null checks are applied to both
 * the frame buffer and the string. String length must be at least 1 or this operation will fail with @ref LOL_BADPARAM.
 * If the string contains an invalid character (i.e. non-ASCII), this operation will fail with @ref LOL_BADCHAR upon
 * reaching the character (which can result in a partial print). ASCII control characters are treated as regular
 * printable characters without regard to their normal control functionality.
 * Uses the current active font map as set by @ref MadLOL_setFont().
 *
 *  @param fb: Frame Buffer to write into.
 *  @param str: String to write into frame buffer.
 *  @param coord: Bottom leftmost pixel in the string block to write.
 *  @param color: Color to draw string as.
 *  @returns Returns @ref LOL_SUCCESS if successful, and an appropriate failure mode otherwise.
 */
MadLOL_Status_t MadLOL_printString(MadLOL_FrameBuffer fb, MadLOL_String str, MadLOL_Coord coord, MadLOL_Color color);

#endif
