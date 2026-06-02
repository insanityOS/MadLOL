#include <stdio.h>
#include "AxLOL_bmp.h"
#include "AxLOL_char.h"
#include "AxLOL_frame_buffer.h"
#include "AxLOL_primitive.h"
#include "AxLOL_string.h"
#include "AxLOL_types.h"

#define IMAGE_WIDTH 320
#define IMAGE_HEIGHT 240

int main(void) {
  static AxLOL_Pixel imageFrame[IMAGE_WIDTH * IMAGE_HEIGHT] = {0};
  const AxLOL_Size frameSize = {.width = IMAGE_WIDTH, .height = IMAGE_HEIGHT};

  AxLOL_FrameBuffer fb = {.frame = imageFrame, .size = frameSize};

  const char filename[] = "test_image.bmp";
  const char message[] = "Hello, World!";
  const char contextMessage[] = "This is a test of AxLOL.";
  const char test0[31] = "THE QUICK BROWN FOX JUMPED";
  const char test1[31] = "OVER THE LAZY DOG";
  const char test2[31] = "the quick brown fox jumped";
  const char test3[31] = "over the lazy dog";

  AxLOL_String filename_str = {.len = sizeof(filename) - 1, .str = (char*)filename};
  AxLOL_String message_str = {.len = sizeof(message) - 1, .str = (char*)message};
  AxLOL_String contextMessage_str = {.len = sizeof(contextMessage) - 1, .str = (char*)contextMessage};
  AxLOL_String test0_str = {.len = 31, .str = (char*)test0};
  AxLOL_String test1_str = {.len = 31, .str = (char*)test1};
  AxLOL_String test2_str = {.len = 31, .str = (char*)test2};
  AxLOL_String test3_str = {.len = 31, .str = (char*)test3};

  AxLOL_Coord filename_coord = {.x = 32, .y = 16};
  AxLOL_Coord message_coord = {.x = 16, .y = IMAGE_HEIGHT - 8};
  AxLOL_Coord contextMessage_coord = {.x = 16, .y = IMAGE_HEIGHT - 9 * 2};
  AxLOL_Coord test0_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 3};
  AxLOL_Coord test1_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 4};
  AxLOL_Coord test2_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 5};
  AxLOL_Coord test3_coord = {.x = 0, .y = IMAGE_HEIGHT - 9 * 6};

  AxLOL_Color color_white = {.R = 31, .G = 63, .B = 31};
  AxLOL_Color color_black = {.R = 0, .G = 0, .B = 0};
  AxLOL_Color color_red = {.R = 31, .G = 0, .B = 0};
  AxLOL_Color color_green = {.R = 0, .G = 63, .B = 0};
  AxLOL_Color color_blue = {.R = 0, .G = 0, .B = 31};
  AxLOL_Color color_0 = {.R = 31, .G = 63, .B = 0};
  AxLOL_Color color_1 = {.R = 31, .G = 0, .B = 31};
  AxLOL_Color color_2 = {.R = 0, .G = 63, .B = 31};

  AxLOL_printString(fb, filename_str, filename_coord, color_white);
  AxLOL_printString(fb, message_str, message_coord, color_red);
  AxLOL_printString(fb, contextMessage_str, contextMessage_coord, color_green);
  AxLOL_printString(fb, test0_str, test0_coord, color_blue);
  AxLOL_printString(fb, test1_str, test1_coord, color_0);
  AxLOL_printString(fb, test2_str, test2_coord, color_1);
  AxLOL_printString(fb, test3_str, test3_coord, color_2);

  AxLOL_fillBlock(fb, (AxLOL_Size){.width = IMAGE_WIDTH, .height = 9 * 3},
                  (AxLOL_Coord){.x = 0, .y = IMAGE_HEIGHT - 9 * 9}, color_white);

  for (uint8_t i = 0; i < 128 - 32; i++) {
    AxLOL_Coord coord = {.x = (i % 40) * 8, .y = IMAGE_HEIGHT - 9 * (7 + (i / 40))};
    AxLOL_putChar(fb, (char)(i + 32), coord, color_black);
  }

  if (!AxLOL_createBMP(fb, filename))
    printf("Aww, this shit ain't working, yo!");

  return 0;
}
