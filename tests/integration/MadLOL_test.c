#include <stdio.h>
#include "MadLOL_bmp.h"
#include "MadLOL_char.h"
#include "MadLOL_frame_buffer.h"
#include "MadLOL_primitive.h"
#include "MadLOL_string.h"
#include "MadLOL_transform_buffer.h"
#include "MadLOL_types.h"

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240

int main(void) {
  static MadLOL_Pixel imageFrame[IMAGE_WIDTH * IMAGE_HEIGHT] = {0};
  static MadLOL_Pixel imageFrame90[IMAGE_WIDTH * IMAGE_HEIGHT] = {0};
  static MadLOL_Pixel imageFrame180[IMAGE_WIDTH * IMAGE_HEIGHT] = {0};
  static MadLOL_Pixel imageFrame270[IMAGE_WIDTH * IMAGE_HEIGHT] = {0};
  const MadLOL_Size frameSize = {.width = IMAGE_WIDTH, .height = IMAGE_HEIGHT};
  const MadLOL_Size frameSizeRotated = {.width = IMAGE_HEIGHT, .height = IMAGE_WIDTH};

  MadLOL_FrameBuffer fb = {.frame = imageFrame, .size = frameSize};
  MadLOL_FrameBuffer fb_90 = {.frame = imageFrame90, .size = frameSizeRotated};
  MadLOL_FrameBuffer fb_180 = {.frame = imageFrame180, .size = frameSize};
  MadLOL_FrameBuffer fb_270 = {.frame = imageFrame270, .size = frameSizeRotated};

  const char filename[] = "test_image.bmp";
  const char filename_90[] = "test_image_rotate90.bmp";
  const char filename_180[] = "test_image_rotate180.bmp";
  const char filename_270[] = "test_image_rotate270.bmp";
  const char message[] = "Hello, World!";
  const char contextMessage[] = "This is a test of MadLOL.";
  const char test0[31] = "THE QUICK BROWN FOX JUMPED";
  const char test1[31] = "OVER THE LAZY DOG";
  const char test2[31] = "the quick brown fox jumped";
  const char test3[31] = "over the lazy dog";

  MadLOL_String filename_str = {.len = sizeof(filename) - 1, .str = (char*)filename};
  MadLOL_String message_str = {.len = sizeof(message) - 1, .str = (char*)message};
  MadLOL_String contextMessage_str = {.len = sizeof(contextMessage) - 1, .str = (char*)contextMessage};
  MadLOL_String test0_str = {.len = 31, .str = (char*)test0};
  MadLOL_String test1_str = {.len = 31, .str = (char*)test1};
  MadLOL_String test2_str = {.len = 31, .str = (char*)test2};
  MadLOL_String test3_str = {.len = 31, .str = (char*)test3};

  MadLOL_Coord filename_coord = {.x = 32, .y = 16};
  MadLOL_Coord message_coord = {.x = 16, .y = IMAGE_HEIGHT - 8};
  MadLOL_Coord contextMessage_coord = {.x = 16, .y = IMAGE_HEIGHT - 9 * 2};
  MadLOL_Coord test0_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 3};
  MadLOL_Coord test1_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 4};
  MadLOL_Coord test2_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 5};
  MadLOL_Coord test3_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 6};

  MadLOL_Color color_white = {.R = 31, .G = 63, .B = 31};
  MadLOL_Color color_black = {.R = 0, .G = 0, .B = 0};
  MadLOL_Color color_red = {.R = 31, .G = 0, .B = 0};
  MadLOL_Color color_green = {.R = 0, .G = 63, .B = 0};
  MadLOL_Color color_blue = {.R = 0, .G = 0, .B = 31};
  MadLOL_Color color_0 = {.R = 31, .G = 63, .B = 0};
  MadLOL_Color color_1 = {.R = 31, .G = 0, .B = 31};
  MadLOL_Color color_2 = {.R = 0, .G = 63, .B = 31};

  MadLOL_printString(fb, filename_str, filename_coord, color_white);
  MadLOL_printString(fb, message_str, message_coord, color_red);
  MadLOL_printString(fb, contextMessage_str, contextMessage_coord, color_green);
  MadLOL_printString(fb, test0_str, test0_coord, color_blue);
  MadLOL_printString(fb, test1_str, test1_coord, color_0);
  MadLOL_printString(fb, test2_str, test2_coord, color_1);
  MadLOL_printString(fb, test3_str, test3_coord, color_2);

  MadLOL_fillBlock(fb, (MadLOL_Size){.width = IMAGE_WIDTH, .height = 9 * 3},
                   (MadLOL_Coord){.x = 0, .y = IMAGE_HEIGHT - 9 * 9}, color_white);

  for (uint8_t i = 0; i < 128 - 32; i++) {
    MadLOL_Coord coord = {.x = (i % 40) * 8, .y = IMAGE_HEIGHT - 9 * (7 + (i / 40))};
    MadLOL_putChar(fb, (char)(i + 32), coord, color_black);
  }

  if (!MadLOL_createBMP(fb, filename))
    printf("Aww, this shit ain't working, yo!");

  MadLOL_rotateBuffer_copy(fb, fb_90, LOL_DEGREES_90);
  MadLOL_rotateBuffer_copy(fb, fb_180, LOL_DEGREES_180);
  MadLOL_rotateBuffer_copy(fb, fb_270, LOL_DEGREES_270);

  MadLOL_createBMP(fb_90, filename_90);
  MadLOL_createBMP(fb_180, filename_180);
  MadLOL_createBMP(fb_270, filename_270);

  return 0;
}
