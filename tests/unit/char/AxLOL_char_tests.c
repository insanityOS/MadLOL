#include "AxLOL_types.h"
#define AXLOL_CREATE_REFERENCE_PIXEL
#include "AxLOL_char.h"
#include "MockAxLOL_primitive.h"
#include "unity.h"

#define TEST_WIDTH_LARGE 320
#define TEST_HEIGHT_LARGE 240

extern AxLOL_FontMap* fontMap_active;

static AxLOL_FontMap fontMap_test = {.char_bitmaps = {}};

void setUp(void) {
  fontMap_active = &AxLOL_defaultFont;
  MockAxLOL_primitive_Init();
}

void tearDown(void) {
  verifyTest();
  MockAxLOL_primitive_Destroy();
}

void verifyTest(void) {
  MockAxLOL_primitive_Verify();
}

void test_setFont_success(void) {
  AxLOL_Status_t status_expected = LOL_SUCCESS;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_setFont(&fontMap_test),
                            "Status for setting font map was not success");

  TEST_ASSERT_EQUAL_HEX64_MESSAGE(&fontMap_test, fontMap_active, "Font map was not properly reset.");
}

void test_setFont_fail_nullPointer(void) {
  AxLOL_Status_t status_expected = LOL_NULLPTR;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_setFont(NULL), "Status for setting font map was not success");

  TEST_ASSERT_EQUAL_HEX64_MESSAGE(&AxLOL_defaultFont, fontMap_active, "Font map was not properly reset.");
}

void test_putChar_success(void) {
  AxLOL_Status_t status_expected = LOL_SUCCESS;

  const AxLOL_Coord coord_test = {0, 0};
  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  const AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = 'f';

  AxLOL_applyPattern_ExpectAndReturn(fb_test, AxLOL_defaultFont.char_bitmaps['f'], coord_test, color_test, LOL_SUCCESS);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

void test_putChar_fail_badChar(void) {
  AxLOL_Status_t status_expected = LOL_BADPARAM;

  const AxLOL_Coord coord_test = {0, 0};
  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  const AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = -50;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

void test_putChar_fail_innerFail(void) {
  AxLOL_Status_t status_expected = LOL_BADPARAM | LOL_INNERFAIL;

  const AxLOL_Coord coord_test = {0, 0};
  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  AxLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (AxLOL_Pixel*)frame_test};
  const AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = 'f';

  AxLOL_applyPattern_ExpectAndReturn(fb_test, AxLOL_defaultFont.char_bitmaps['f'], coord_test, color_test,
                                     LOL_BADPARAM);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

void test_putChar_fail_nullPointer(void) {
  AxLOL_Status_t status_expected = LOL_NULLPTR;

  const AxLOL_Coord coord_test = {0, 0};
  const AxLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  AxLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = NULL};
  const AxLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = 'f';

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_setFont_success);
  RUN_TEST(test_setFont_fail_nullPointer);
  RUN_TEST(test_putChar_success);
  RUN_TEST(test_putChar_fail_badChar);
  RUN_TEST(test_putChar_fail_innerFail);
  RUN_TEST(test_putChar_fail_nullPointer);

  return UNITY_END();
}
