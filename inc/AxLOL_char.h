/*! @file AxLOL_char.h
 *  @brief AxLOL character operations and definitions.
 *
 * Definitions for AxLOL character operations and types, such as placing characters, defining font packs, and selecting
 * the active font pack. Includes a default reference 8x8 font pack. Quality of this font pack is NOT guaranteed, or
 * even claimed.
 */

#ifndef AXLOL_CHAR_H
#define AXLOL_CHAR_H

#include "AxLOL_primitive.h"

/*! @brief Font Map type definition.
 *
 * Font Map type definition. Supports monospace and variable-width fonts.
 *
 *  @var AxLOL_FontMap::char_bitmaps Patterns for ASCII character patterns.
 */
typedef struct {
  AxLOL_Pattern char_bitmaps[128];
} AxLOL_FontMap;

/*! @brief Default reference font pack.
 *
 * Default reference font pack. Exposed so users may revert to using the default font after changing the active font, if
 * so desired.
 */
extern AxLOL_FontMap AxLOL_defaultFont;

/*! @brief Set the active font map.
 *
 * Sets the active font map. Note that this only affects newly-printed characters; previously-printed characters are
 * unaffected by changes to font map. Note that the font map is not checked for validity; an improperly defined font map
 * may therefore cause an error at a later time.
 *
 *  @param fontMap: Pointer to the font map from which to print new characters.
 *  @returns Returns @ref LOL_SUCCESS if the operation is successful, @ref LOL_NULLPTR if provided pointer is a null
 *  pointer.
 *  @post New font pack will be printed from on next character operation.
 *  @warning The font pack is not checked for validity.
 */
AxLOL_Status_t AxLOL_setFont(AxLOL_FontMap* fontMap);

/*! @brief Puts a character into the Frame Buffer.
 *
 * Puts character @c c into the Frame Buffer. The character is selected from the active font map, and printed at
 * location @c coord in @c color. Note that the character pattern may be truncated if the coordinate places it partially
 * out of bounds. If the character is fully out of bounds or is otherwise badly defined, @ref AxLOL_applyPattern() will
 * return a failure status, which will be augmented with @ref LOL_INNERFAIL. If the character is outside of standard
 * ASCII definitions (i.e. above 127), this function will return @ref LOL_BADPARAM (no @ref LOL_INNERFAIL). If @c fb is
 * NULL, this returns @ref LOL_NULLPTR (no @ref LOL_INNERFAIL).
 *
 *  @param fb: Frame Buffer in which to print a character.
 *  @param c: Character to print into @c fb.
 *  @param coord: Where in @c fb to print @c c.
 *  @param color: What color to print @c c.
 *  @returns Returns @ref LOL_SUCCESS if successful, relevant failure status otherwise.
 */
AxLOL_Status_t AxLOL_putChar(AxLOL_FrameBuffer fb, char c, AxLOL_Coord coord, AxLOL_Color color);

#endif
