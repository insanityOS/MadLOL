#include "MadLOL_string.h"
#include "MadLOL_char.h"
#include "MadLOL_types.h"

// Cheekily grabbing the active font map to manage setting the coordinate for the next character.
extern MadLOL_FontMap* fontMap_active;

MadLOL_Status_t MadLOL_printString(MadLOL_FrameBuffer fb, MadLOL_String str, MadLOL_Coord coord, MadLOL_Color color) {
  MadLOL_Status_t status_persistent = LOL_BADBOUNDS;
  MadLOL_Status_t status_immediate = LOL_SUCCESS;
  MadLOL_Coord coord_next = coord;

  if ((!(fb.frame)) || (!(str.str)))
    return LOL_NULLPTR;

  if (str.len == 0)
    return LOL_BADPARAM;

  for (uint16_t i = 0; i < str.len; i++) {
    char c_next = str.str[i];

    if (0x80 & c_next)
      return LOL_BADCHAR;

    status_immediate = MadLOL_putChar(fb, c_next, coord_next, color);

    if (status_immediate & (LOL_BADCHAR | LOL_NULLPTR | LOL_BADPARAM))
      return (status_immediate | LOL_INNERFAIL);

    status_persistent &= status_immediate;

    coord_next.x += fontMap_active->char_bitmaps[(uint8_t)c_next].size.width;
  }

  return status_persistent;
}
