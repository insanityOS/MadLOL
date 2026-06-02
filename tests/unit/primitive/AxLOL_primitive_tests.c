#include <string.h>
#include "AxLOL_types.h"
#define AXLOL_CREATE_REFERENCE_PIXEL
#include "AxLOL_primitive.h"
#include "MockAxLOL_frame_buffer.h"
#include "unity.h"

#define TEST_WIDTH_SMALL 32
#define TEST_HEIGHT_SMALL 24
#define TEST_WIDTH_LARGE 320
#define TEST_HEIGHT_LARGE 240
#define TEST_RB 31
#define TEST_G 63

static AxLOL_Pixel* pixel_forCallback[64] = {NULL};
static AxLOL_Status_t status_forCallback = LOL_SUCCESS;

void setUp(void) {
  status_forCallback = LOL_SUCCESS;
  memset(pixel_forCallback, 0, sizeof(pixel_forCallback));
  MockAxLOL_frame_buffer_Init();
}

void tearDown(void) {
  verifyTest();
  MockAxLOL_frame_buffer_Destroy();
}

void verifyTest(void) {
  MockAxLOL_frame_buffer_Verify();
}

AxLOL_Status_t callback_AxLOL_setColor(AxLOL_Pixel* pixel,
                                       __attribute__((__unused__)) AxLOL_Color color,
                                       int NumCalls) {
  if (NumCalls >= 64)
    TEST_ABORT();
  if (pixel != pixel_forCallback[NumCalls])
    TEST_FAIL_MESSAGE("Didn't see expected pixel");

  return status_forCallback;
}

void test_applyPattern_success_allIn(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (int32_t i = 0; i < 8; i++) {
    for (int32_t j = 7; j >= 0; j--) {
      if ((i % 2) != (j % 2))
        AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, status_expected);
    }
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_success_edgeLowerLeft(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {-7, -5};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  pixel_forCallback[0] = &frame_test[TEST_WIDTH_LARGE];

  AxLOL_setColor_ExpectAndReturn(&frame_test[TEST_WIDTH_LARGE], color_test, status_expected);
  AxLOL_setColor_AddCallback(&callback_AxLOL_setColor);

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
  verifyTest();
}

void test_applyPattern_success_edgeUpperRight(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {TEST_WIDTH_LARGE - 1, TEST_HEIGHT_LARGE - 5};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  pixel_forCallback[0] = &frame_test[(TEST_WIDTH_LARGE - 1) + (TEST_WIDTH_LARGE * (TEST_HEIGHT_LARGE - 4))];
  pixel_forCallback[1] = &frame_test[(TEST_WIDTH_LARGE - 1) + (TEST_WIDTH_LARGE * (TEST_HEIGHT_LARGE - 2))];
  AxLOL_setColor_ExpectAndReturn(&frame_test[(TEST_WIDTH_LARGE - 1) + (TEST_WIDTH_LARGE * (TEST_HEIGHT_LARGE - 2))],
                                 color_test, status_expected);
  AxLOL_setColor_ExpectAndReturn(&frame_test[(TEST_WIDTH_LARGE - 1) + (TEST_WIDTH_LARGE * (TEST_HEIGHT_LARGE - 4))],
                                 color_test, status_expected);
  AxLOL_setColor_AddCallback(&callback_AxLOL_setColor);

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_badParam_above(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {0, TEST_HEIGHT_LARGE};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_badParam_below(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {0, -TEST_HEIGHT_SMALL};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_badParam_right(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {TEST_WIDTH_LARGE, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_badParam_left(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {-TEST_WIDTH_SMALL, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_badParam_patternWidth(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 0, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {1, 1};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_badParam_patternHeight(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 0}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {1, 1};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_nullPointerFrame(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = NULL};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_nullPointerPattern(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = NULL};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_setColor_first(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  AxLOL_setColor_ExpectAndReturn(&frame_test[0 + TEST_WIDTH_LARGE * 0], color_test, LOL_NULLPTR);

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_applyPattern_fail_setColor_last(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const uint8_t bitmap[1][8] = {{0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55}};
  const AxLOL_Pattern pattern_test = {.size = {.width = 8, .height = 8}, .bitmap = (uint8_t*)bitmap};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  int callCount = 0;
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      if ((i % 2) != (j % 2)) {
        if (++callCount < 32) {
          AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, LOL_SUCCESS);
        } else {
          AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, LOL_NULLPTR);
        }
      }
    }
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_applyPattern(fb_test, pattern_test, coord_test, color_test));
}

void test_fillBlock_success_allIn(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = 6, .height = 6};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 6; j++) {
      pixel_forCallback[i + j * 6] = &frame_test[i + TEST_WIDTH_LARGE * j];
      AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, status_expected);
    }
  }

  AxLOL_setColor_AddCallback(&callback_AxLOL_setColor);

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_success_edgeLowerLeft(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  // Explanation: Only the last vertical set of pixels are in bounds here.
  const AxLOL_Coord coord_test = {1 - TEST_WIDTH_SMALL, -5};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (size_t j = 5; j < TEST_HEIGHT_SMALL; j++) {
    AxLOL_setColor_ExpectAndReturn(&frame_test[0 + TEST_WIDTH_LARGE * j], color_test, status_expected);
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_success_edgeUpperRight(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  // Explanation: Only the last vertical set of pixels are in bounds here.
  const AxLOL_Coord coord_test = {TEST_WIDTH_LARGE - 1, TEST_HEIGHT_LARGE - 10};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (size_t j = TEST_HEIGHT_LARGE - 10; j < TEST_HEIGHT_LARGE; j++) {
    AxLOL_setColor_ExpectAndReturn(&frame_test[0 + TEST_WIDTH_LARGE * j], color_test, status_expected);
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_badParam_above(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {0, TEST_HEIGHT_LARGE};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_badParam_below(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {0, -TEST_HEIGHT_SMALL};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_badParam_right(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {TEST_WIDTH_LARGE, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_badParam_left(void) {
  const AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {-TEST_WIDTH_SMALL, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_nullPointer(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = NULL};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_setColor_first(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  AxLOL_setColor_ExpectAndReturn(NULL, color_test, LOL_NULLPTR);
  AxLOL_setColor_IgnoreArg_pixel();

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_fillBlock_fail_setColor_last(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  const AxLOL_Size blockSize_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  const AxLOL_Coord coord_test = {0, 0};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (size_t i = 0; i < TEST_WIDTH_SMALL; i++) {
    for (size_t j = 0; j < TEST_HEIGHT_SMALL; j++) {
      if ((i == TEST_WIDTH_SMALL - 1) && (j == TEST_HEIGHT_SMALL - 1))
        AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, LOL_NULLPTR);
      else
        AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, LOL_SUCCESS);
    }
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_fillBlock(fb_test, blockSize_test, coord_test, color_test));
}

void test_paintBuffer_success(void) {
  const AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Size size_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  AxLOL_Pixel frame_test[TEST_WIDTH_SMALL * TEST_HEIGHT_SMALL] = {0};
  AxLOL_FrameBuffer fb_test = {.size = size_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (size_t i = 0; i < TEST_WIDTH_SMALL; i++) {
    for (size_t j = 0; j < TEST_HEIGHT_SMALL; j++) {
      AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_SMALL * j], color_test, status_expected);
    }
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_paintBuffer(fb_test, color_test));
}

void test_paintBuffer_fail_nullPointer(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR;

  const AxLOL_Size size_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  AxLOL_FrameBuffer fb_test = {.size = size_test, .frame = NULL};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  TEST_ASSERT_EQUAL(status_expected, AxLOL_paintBuffer(fb_test, color_test));
}

void test_paintBuffer_fail_setColor_first(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const AxLOL_Size size_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  AxLOL_Pixel frame_test[TEST_WIDTH_SMALL * TEST_HEIGHT_SMALL] = {0};
  AxLOL_FrameBuffer fb_test = {.size = size_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  AxLOL_setColor_ExpectAndReturn(&frame_test[0], color_test, LOL_NULLPTR);

  TEST_ASSERT_EQUAL(status_expected, AxLOL_paintBuffer(fb_test, color_test));
}

void test_paintBuffer_fail_setColor_last(void) {
  const AxLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const AxLOL_Size size_test = {.width = TEST_WIDTH_SMALL, .height = TEST_HEIGHT_SMALL};
  AxLOL_Pixel frame_test[TEST_WIDTH_SMALL * TEST_HEIGHT_SMALL] = {};
  AxLOL_FrameBuffer fb_test = {.size = size_test, .frame = (AxLOL_Pixel*)frame_test};
  AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};

  for (size_t i = 0; i < TEST_WIDTH_SMALL; i++) {
    for (size_t j = 0; j < TEST_HEIGHT_SMALL; j++) {
      if ((i == TEST_WIDTH_SMALL - 1) && (j == TEST_HEIGHT_SMALL - 1))
        AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, LOL_NULLPTR);
      else
        AxLOL_setColor_ExpectAndReturn(&frame_test[i + TEST_WIDTH_LARGE * j], color_test, LOL_SUCCESS);

      AxLOL_setColor_IgnoreArg_pixel();
    }
  }

  TEST_ASSERT_EQUAL(status_expected, AxLOL_paintBuffer(fb_test, color_test));
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_applyPattern_success_allIn);
  RUN_TEST(test_applyPattern_success_edgeLowerLeft);
  RUN_TEST(test_applyPattern_success_edgeUpperRight);
  RUN_TEST(test_applyPattern_fail_badParam_above);
  RUN_TEST(test_applyPattern_fail_badParam_below);
  RUN_TEST(test_applyPattern_fail_badParam_right);
  RUN_TEST(test_applyPattern_fail_badParam_left);
  RUN_TEST(test_applyPattern_fail_badParam_patternWidth);
  RUN_TEST(test_applyPattern_fail_badParam_patternHeight);
  RUN_TEST(test_applyPattern_fail_nullPointerFrame);
  RUN_TEST(test_applyPattern_fail_nullPointerPattern);
  RUN_TEST(test_applyPattern_fail_setColor_first);
  RUN_TEST(test_applyPattern_fail_setColor_last);
  RUN_TEST(test_fillBlock_success_allIn);
  RUN_TEST(test_fillBlock_success_edgeLowerLeft);
  RUN_TEST(test_fillBlock_success_edgeUpperRight);
  RUN_TEST(test_fillBlock_fail_badParam_above);
  RUN_TEST(test_fillBlock_fail_badParam_below);
  RUN_TEST(test_fillBlock_fail_badParam_right);
  RUN_TEST(test_fillBlock_fail_badParam_left);
  RUN_TEST(test_fillBlock_fail_nullPointer);
  RUN_TEST(test_fillBlock_fail_setColor_first);
  RUN_TEST(test_fillBlock_fail_setColor_last);
  RUN_TEST(test_paintBuffer_success);
  RUN_TEST(test_paintBuffer_fail_nullPointer);
  RUN_TEST(test_paintBuffer_fail_setColor_first);
  RUN_TEST(test_paintBuffer_fail_setColor_last);

  return UNITY_END();
}
