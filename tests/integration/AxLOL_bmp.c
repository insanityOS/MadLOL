#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "AxLOL_bmp.h"
#include "AxLOL_frame_buffer.h"

typedef struct __attribute__((__packed__)) {
  uint16_t bfType;
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
} AxLOL_BMPHeader;

typedef struct __attribute__((__packed__)) {
  uint32_t biSize;
  int32_t biWidth;
  int32_t biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
} AxLOL_BMPInfoHeader;

bool AxLOL_createBMP(AxLOL_FrameBuffer fb, const char filename[]) {
  uint16_t bitcount = 16;
  uint32_t width_in_bytes = ((fb.size.width * bitcount + 15) / 16) * 2;
  uint32_t image_size = width_in_bytes * fb.size.height;

  AxLOL_BMPHeader header = {.bfSize = image_size + 54, .bfOffBits = 54};

  // Magic bullshit for telling image rendering program that this is, in fact, a bitmap.
  memcpy(&header, "BM", 2);
  AxLOL_BMPInfoHeader infoHeader = {.biSize = 40,
                                    .biPlanes = 1,
                                    .biWidth = fb.size.width,
                                    .biHeight = fb.size.height,
                                    .biBitCount = bitcount,
                                    .biSizeImage = image_size};

  if ((sizeof(AxLOL_BMPHeader) != 14) || (sizeof(AxLOL_BMPInfoHeader) != 40)) {
    printf("BMP headers are mis-sized. Giving up.");
    return false;
  }

  if (!fb.frame || !filename) {
    printf("Uh, this is a null pointer, sir?");
    return false;
  }

  FILE* fout = fopen(filename, "wb");
  if (!fout) {
    printf("Can't open this filename, WTF?");
    return false;
  }

  fwrite(&header, sizeof(header), 1, fout);
  fwrite(&infoHeader, sizeof(infoHeader), 1, fout);
  fwrite((char*)fb.frame, 1, image_size, fout);
  fclose(fout);

  return true;
}
