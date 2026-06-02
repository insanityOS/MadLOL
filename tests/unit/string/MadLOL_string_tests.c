#define MADLOL_CREATE_REFERENCE_PIXEL
#include "MadLOL_string.h"
#include "MadLOL_types.h"
#include "MockMadLOL_char.h"
#include "unity.h"

#define TEST_WIDTH_LARGE 320
#define TEST_HEIGHT_LARGE 240

void setUp(void) {
  MockMadLOL_char_Init();
}

void tearDown(void) {
  verifyTest();
  MockMadLOL_char_Destroy();
}

void verifyTest(void) {
  MockMadLOL_char_Verify();
}

void test_printString_success_allIn(void) {
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  for (size_t i = 0; i < 12; i++) {
    MadLOL_Coord coord_expected = coord_test;
    coord_expected.x += i * 8;
    MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[i], coord_expected, color_test, LOL_SUCCESS);
  }

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status was not success.");
}

void test_printString_success_partiallyIn(void) {
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  for (size_t i = 0; i < 11; i++) {
    MadLOL_Coord coord_expected = coord_test;
    coord_expected.x += i * 8;
    MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[i], coord_expected, color_test, LOL_BADBOUNDS);
  }

  MadLOL_Coord coord_expected = coord_test;
  coord_expected.x += 11 * 8;
  MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[11], coord_expected, color_test, LOL_SUCCESS);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status was not success.");
}

void test_printString_fail_badBounds(void) {
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  for (size_t i = 0; i < 12; i++) {
    MadLOL_Coord coord_expected = coord_test;
    coord_expected.x += i * 8;
    MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[i], coord_expected, color_test, LOL_BADBOUNDS);
  }

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status was not bounds fault.");
}

void test_printString_fail_badStrLen(void) {
  MadLOL_Status_t status_expected = LOL_BADPARAM;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {0, strstr_test};

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not flag zero-length string.");
}

void test_printString_fail_badChar(void) {
  MadLOL_Status_t status_expected = LOL_BADCHAR;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "\x96 llo, World!";
  MadLOL_String str_test = {12, strstr_test};

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not indicate invalid character.");
}

void test_printString_fail_innerBadParam(void) {
  MadLOL_Status_t status_expected = LOL_BADPARAM | LOL_INNERFAIL;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[0], coord_test, color_test, LOL_BADPARAM);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not indicate internal error.");
}

void test_printString_fail_innerNullPointer(void) {
  MadLOL_Status_t status_expected = LOL_NULLPTR | LOL_INNERFAIL;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[0], coord_test, color_test, LOL_NULLPTR);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not indicate internal error.");
}

void test_printString_fail_innerBadChar(void) {
  MadLOL_Status_t status_expected = LOL_BADCHAR | LOL_INNERFAIL;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  MadLOL_putChar_ExpectAndReturn(fb_test, str_test.str[0], coord_test, color_test, LOL_BADCHAR);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not indicate internal error.");
}

void test_printString_fail_nullPointer_fb(void) {
  MadLOL_Status_t status_expected = LOL_NULLPTR;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = NULL};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  char strstr_test[16] = "Hello, World!";
  MadLOL_String str_test = {12, strstr_test};

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not flag null pointer.");
}

void test_printString_fail_nullPointer_str(void) {
  MadLOL_Status_t status_expected = LOL_NULLPTR;

  const MadLOL_Coord coord_test = {0, 0};
  const MadLOL_Size frameSize_test = {.width = TEST_WIDTH_LARGE, .height = TEST_HEIGHT_LARGE};
  MadLOL_Pixel frame_test[TEST_WIDTH_LARGE * TEST_HEIGHT_LARGE] = {0};
  MadLOL_FrameBuffer fb_test = {.size = frameSize_test, .frame = (MadLOL_Pixel*)frame_test};
  const MadLOL_Color color_test = {.R = 31, .G = 63, .B = 31};
  MadLOL_String str_test = {12, NULL};

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_printString(fb_test, str_test, coord_test, color_test),
                            "Returned status did not flag null pointer.");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_printString_success_allIn);
  RUN_TEST(test_printString_success_partiallyIn);
  RUN_TEST(test_printString_fail_badBounds);
  RUN_TEST(test_printString_fail_badStrLen);
  RUN_TEST(test_printString_fail_badChar);
  RUN_TEST(test_printString_fail_innerBadChar);
  RUN_TEST(test_printString_fail_innerBadParam);
  RUN_TEST(test_printString_fail_innerNullPointer);
  RUN_TEST(test_printString_fail_nullPointer_fb);
  RUN_TEST(test_printString_fail_nullPointer_str);

  return UNITY_END();
}

#define DEF_SIZE ((MadLOL_Size){.width = 8, .height = 8})

MadLOL_FontMap MadLOL_defaultFont = {.char_bitmaps = {
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x00,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x14,
                                                                  0x14,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x24,
                                                                  0x24,
                                                                  0xFF,
                                                                  0x24,
                                                                  0x24,
                                                                  0xFF,
                                                                  0x24,
                                                                  0x24,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x10,
                                                                  0x7C,
                                                                  0x50,
                                                                  0x7C,
                                                                  0x14,
                                                                  0x7C,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x62,
                                                                  0x64,
                                                                  0x08,
                                                                  0x10,
                                                                  0x26,
                                                                  0x46,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x38,
                                                                  0x24,
                                                                  0x28,
                                                                  0x10,
                                                                  0x3A,
                                                                  0x24,
                                                                  0x3A,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x10,
                                                                  0x10,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x10,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x08,
                                                                  0x04,
                                                                  0x04,
                                                                  0x04,
                                                                  0x04,
                                                                  0x04,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x2A,
                                                                  0x1C,
                                                                  0x3E,
                                                                  0x1C,
                                                                  0x2A,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x08,
                                                                  0x08,
                                                                  0x3E,
                                                                  0x08,
                                                                  0x08,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x08,
                                                                  0x08,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x3E,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x04,
                                                                  0x08,
                                                                  0x08,
                                                                  0x10,
                                                                  0x10,
                                                                  0x20,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x3C,
                                                                  0x46,
                                                                  0x4A,
                                                                  0x4A,
                                                                  0x52,
                                                                  0x62,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x08,
                                                                  0x18,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x3E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x1C,
                                                                  0x22,
                                                                  0x02,
                                                                  0x04,
                                                                  0x08,
                                                                  0x10,
                                                                  0x3E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x1C,
                                                                  0x22,
                                                                  0x02,
                                                                  0x0C,
                                                                  0x02,
                                                                  0x22,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x08,
                                                                  0x48,
                                                                  0x48,
                                                                  0x48,
                                                                  0x7E,
                                                                  0x08,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7E,
                                                                  0x40,
                                                                  0x7C,
                                                                  0x02,
                                                                  0x02,
                                                                  0x44,
                                                                  0x38,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x04,
                                                                  0x08,
                                                                  0x10,
                                                                  0x2C,
                                                                  0x22,
                                                                  0x22,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x3E,
                                                                  0x02,
                                                                  0x04,
                                                                  0x3E,
                                                                  0x08,
                                                                  0x10,
                                                                  0x20,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x3C,
                                                                  0x42,
                                                                  0x42,
                                                                  0x3C,
                                                                  0x42,
                                                                  0x42,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x38,
                                                                  0x44,
                                                                  0x44,
                                                                  0x34,
                                                                  0x08,
                                                                  0x10,
                                                                  0x20,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                                  0x00,
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                                  0x00,
                                                                  0x18,
                                                                  0x08,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x08,
                                                                  0x10,
                                                                  0x20,
                                                                  0x10,
                                                                  0x08,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x3C,
                                                                  0x00,
                                                                  0x00,
                                                                  0x3C,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x20,
                                                                  0x10,
                                                                  0x08,
                                                                  0x10,
                                                                  0x20,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x3C,
                                                                  0x42,
                                                                  0x02,
                                                                  0x0C,
                                                                  0x10,
                                                                  0x00,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x1C,
                                                                  0x22,
                                                                  0x4E,
                                                                  0x4A,
                                                                  0x2E,
                                                                  0x10,
                                                                  0x0E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x18,
                                                                  0x3C,
                                                                  0x66,
                                                                  0x66,
                                                                  0x7E,
                                                                  0x66,
                                                                  0x66,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7C,
                                                                  0x62,
                                                                  0x62,
                                                                  0x7C,
                                                                  0x62,
                                                                  0x62,
                                                                  0x7C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x1C,
                                                                  0x36,
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x36,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7C,
                                                                  0x66,
                                                                  0x62,
                                                                  0x62,
                                                                  0x62,
                                                                  0x66,
                                                                  0x7C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7E,
                                                                  0x60,
                                                                  0x60,
                                                                  0x78,
                                                                  0x60,
                                                                  0x60,
                                                                  0x7E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7E,
                                                                  0x60,
                                                                  0x60,
                                                                  0x78,
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x1C,
                                                                  0x36,
                                                                  0x60,
                                                                  0x6E,
                                                                  0x62,
                                                                  0x36,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x46,
                                                                  0x46,
                                                                  0x46,
                                                                  0x7E,
                                                                  0x46,
                                                                  0x46,
                                                                  0x46,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7E,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x7E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x06,
                                                                  0x06,
                                                                  0x06,
                                                                  0x06,
                                                                  0x66,
                                                                  0x7E,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x62,
                                                                  0x64,
                                                                  0x68,
                                                                  0x70,
                                                                  0x68,
                                                                  0x64,
                                                                  0x62,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x7E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x42,
                                                                  0x66,
                                                                  0x5A,
                                                                  0x42,
                                                                  0x42,
                                                                  0x42,
                                                                  0x42,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x42,
                                                                  0x62,
                                                                  0x72,
                                                                  0x5A,
                                                                  0x4E,
                                                                  0x46,
                                                                  0x42,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x3C,
                                                                  0x66,
                                                                  0x42,
                                                                  0x42,
                                                                  0x42,
                                                                  0x66,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7C,
                                                                  0x66,
                                                                  0x66,
                                                                  0x7C,
                                                                  0x60,
                                                                  0x60,
                                                                  0x60,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x38,
                                                                  0x6C,
                                                                  0x44,
                                                                  0x44,
                                                                  0x44,
                                                                  0x6C,
                                                                  0x3A,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7C,
                                                                  0x66,
                                                                  0x66,
                                                                  0x7C,
                                                                  0x78,
                                                                  0x6C,
                                                                  0x66,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x3C,
                                                                  0x62,
                                                                  0x40,
                                                                  0x3C,
                                                                  0x02,
                                                                  0x46,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7E,
                                                                  0x7E,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x66,
                                                                  0x66,
                                                                  0x66,
                                                                  0x66,
                                                                  0x66,
                                                                  0x66,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x42,
                                                                  0x44,
                                                                  0x44,
                                                                  0x48,
                                                                  0x48,
                                                                  0x50,
                                                                  0x20,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x42,
                                                                  0x42,
                                                                  0x42,
                                                                  0x5A,
                                                                  0x5A,
                                                                  0x5A,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x42,
                                                                  0x24,
                                                                  0x24,
                                                                  0x18,
                                                                  0x24,
                                                                  0x24,
                                                                  0x42,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x42,
                                                                  0x42,
                                                                  0x24,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x7E,
                                                                  0x7E,
                                                                  0x04,
                                                                  0x08,
                                                                  0x10,
                                                                  0x20,
                                                                  0x7E,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x38,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x38,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x20,
                                                                  0x10,
                                                                  0x10,
                                                                  0x08,
                                                                  0x08,
                                                                  0x04,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x1C,
                                                                  0x04,
                                                                  0x04,
                                                                  0x04,
                                                                  0x04,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x10,
                                                                  0x28,
                                                                  0x44,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0xFF,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x10,
                                                                  0x10,
                                                                  0x08,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x3C,
                                                                  0x02,
                                                                  0x3E,
                                                                  0x66,
                                                                  0x3A,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x40,
                                                                  0x40,
                                                                  0x7C,
                                                                  0x46,
                                                                  0x46,
                                                                  0x7C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x1C,
                                                                  0x22,
                                                                  0x40,
                                                                  0x40,
                                                                  0x22,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x02,
                                                                  0x02,
                                                                  0x3E,
                                                                  0x62,
                                                                  0x62,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x3C,
                                                                  0x42,
                                                                  0x7E,
                                                                  0x40,
                                                                  0x42,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x0C,
                                                                  0x12,
                                                                  0x10,
                                                                  0x7C,
                                                                  0x10,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x1A,
                                                                  0x26,
                                                                  0x26,
                                                                  0x1A,
                                                                  0x42,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x40,
                                                                  0x40,
                                                                  0x58,
                                                                  0x64,
                                                                  0x44,
                                                                  0x44,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x18,
                                                                  0x00,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x02,
                                                                  0x00,
                                                                  0x02,
                                                                  0x02,
                                                                  0x22,
                                                                  0x1C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x20,
                                                                  0x24,
                                                                  0x28,
                                                                  0x38,
                                                                  0x2C,
                                                                  0x22,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x20,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x28,
                                                                  0x54,
                                                                  0x54,
                                                                  0x54,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x58,
                                                                  0x64,
                                                                  0x44,
                                                                  0x44,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x18,
                                                                  0x24,
                                                                  0x24,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x38,
                                                                  0x24,
                                                                  0x38,
                                                                  0x20,
                                                                  0x20,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x38,
                                                                  0x48,
                                                                  0x38,
                                                                  0x08,
                                                                  0x08,
                                                                  0x06,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x58,
                                                                  0x64,
                                                                  0x40,
                                                                  0x40,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x1C,
                                                                  0x20,
                                                                  0x18,
                                                                  0x04,
                                                                  0x38,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x08,
                                                                  0x08,
                                                                  0x1C,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x24,
                                                                  0x24,
                                                                  0x24,
                                                                  0x1A,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x44,
                                                                  0x44,
                                                                  0x28,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x22,
                                                                  0x22,
                                                                  0x2A,
                                                                  0x14,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x22,
                                                                  0x14,
                                                                  0x08,
                                                                  0x14,
                                                                  0x22,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x24,
                                                                  0x24,
                                                                  0x1C,
                                                                  0x04,
                                                                  0x24,
                                                                  0x18,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x3C,
                                                                  0x08,
                                                                  0x10,
                                                                  0x3C,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x08,
                                                                  0x10,
                                                                  0x10,
                                                                  0x20,
                                                                  0x10,
                                                                  0x10,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x08,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x10,
                                                                  0x08,
                                                                  0x08,
                                                                  0x04,
                                                                  0x08,
                                                                  0x08,
                                                                  0x10,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x20,
                                                                  0x52,
                                                                  0x0C,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                         (MadLOL_Pattern){.size = DEF_SIZE,
                                                          .bitmap =
                                                              (uint8_t[8]){
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                                  0x00,
                                                              }},
                                     }};
MadLOL_FontMap* fontMap_active = &MadLOL_defaultFont;
