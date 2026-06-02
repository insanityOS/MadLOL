#include "MadLOL_types.h"
#define MADLOL_CREATE_REFERENCE_PIXEL
#include "MadLOL_char.h"
#include "MockMadLOL_primitive.h"
#include "unity.h"

#define TEST_WIDTH_LARGE 320
#define TEST_HEIGHT_LARGE 240

extern MadLOL_FontMap* fontMap_active;

static MadLOL_FontMap fontMap_test = {.char_bitmaps = {}};

void setUp(void) {
  fontMap_active = &MadLOL_defaultFont;
  MockMadLOL_primitive_Init();
}

void tearDown(void) {
  verifyTest();
  MockMadLOL_primitive_Destroy();
}

void verifyTest(void) {
  MockMadLOL_primitive_Verify();
}

void test_setFont_success(void) {
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_setFont(&fontMap_test),
                            "Status for setting font map was not success");

  TEST_ASSERT_EQUAL_HEX64_MESSAGE(&fontMap_test, fontMap_active, "Font map was not properly reset.");
}

void test_setFont_fail_nullPointer(void) {
  MadLOL_Status_t status_expected = LOL_NULLPTR;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_setFont(NULL), "Status for setting font map was not success");

  TEST_ASSERT_EQUAL_HEX64_MESSAGE(&MadLOL_defaultFont, fontMap_active, "Font map was not properly reset.");
}

void test_putChar_success(void) {
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = 'f';

  MadLOL_applyPattern_ExpectAndReturn(fb_test, MadLOL_defaultFont.char_bitmaps['f'], coord_test, color_test,
                                      LOL_SUCCESS);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

void test_putChar_fail_badChar(void) {
  MadLOL_Status_t status_expected = LOL_BADCHAR;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = -50;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

void test_putChar_fail_innerFail(void) {
  MadLOL_Status_t status_expected = LOL_BADPARAM | LOL_INNERFAIL;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = 'f';

  MadLOL_applyPattern_ExpectAndReturn(fb_test, MadLOL_defaultFont.char_bitmaps['f'], coord_test, color_test,
                                      LOL_BADPARAM);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_putChar(fb_test, c_test, coord_test, color_test),
                            "Incorrect return status!");
}

void test_putChar_fail_nullPointer(void) {
  MadLOL_Status_t status_expected = LOL_NULLPTR;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = NULL};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  const char c_test = 'f';

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_putChar(fb_test, c_test, coord_test, color_test),
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
