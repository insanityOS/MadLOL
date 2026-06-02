#ifndef AXLOL_BMP_H
#define AXLOL_BMP_H

#include <stdbool.h>
#include <stddef.h>
#include "AxLOL_frame_buffer.h"

/*! @brief Generate a BMP file.
 *
 * Creates a BMP file of the provided frame buffer. Requires modification if the reference pixel format is not used.
 *
 *  @param fb: Frame Buffer from which to generate BMP image.
 *  @param filename: Filename for the generated BMP image.
 *  @warning @c filename is NOT sanitized internally.
 */
bool AxLOL_createBMP(AxLOL_FrameBuffer fb, const char filename[]);

#endif
