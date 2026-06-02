#include "AxLOL_string.h"
#include "AxLOL_char.h"
#include "AxLOL_types.h"

// Cheekily grabbing the active font map to manage setting the coordinate for the next character.
extern AxLOL_FontMap* fontMap_active;

AxLOL_Status_t AxLOL_printString(AxLOL_FrameBuffer fb, AxLOL_String str, AxLOL_Coord coord, AxLOL_Color color) {
  AxLOL_Status_t status_persistent = LOL_BADBOUNDS;
  AxLOL_Status_t status_immediate = LOL_SUCCESS;
  AxLOL_Coord coord_next = coord;

  if ((!(fb.frame)) || (!(str.str)))
    return LOL_NULLPTR;

  if (str.len == 0)
    return LOL_BADPARAM;

  for (uint16_t i = 0; i < str.len; i++) {
    char c_next = str.str[i];

    if (0x80 & c_next)
      return LOL_BADCHAR;

    status_immediate = AxLOL_putChar(fb, c_next, coord_next, color);

    if (status_immediate & (LOL_BADCHAR | LOL_NULLPTR | LOL_BADPARAM))
      return (status_immediate | LOL_INNERFAIL);

    status_persistent &= status_immediate;

    coord_next.x += fontMap_active->char_bitmaps[(uint8_t)c_next].size.width;
  }

  return status_persistent;
}
