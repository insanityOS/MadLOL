#define AXLOL_CREATE_REFERENCE_PIXEL
#include "AxLOL_frame_buffer.h"
#include "AxLOL_types.h"
#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_setColor_fail_rejectsNull(void) {
  AxLOL_Status_t status_expected = LOL_NULLPTR;
  AxLOL_Color color_test = {0};

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_setColor(NULL, color_test), "FUT did not reject null pointer");
}

void test_setColor_success(void) {
  static AxLOL_Pixel pixel_test = {.color = {.R = 0, .G = 0, .B = 0}};
  AxLOL_Status_t status_expected = LOL_SUCCESS;
  AxLOL_Color color_test = {.R = 15, .G = 33, .B = 5};

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, AxLOL_setColor(&pixel_test, color_test),
                            "FUT returned non-success status");
  TEST_ASSERT_EQUAL_MESSAGE(color_test.R, pixel_test.color.R, "R channel did not match expected");
  TEST_ASSERT_EQUAL_MESSAGE(color_test.G, pixel_test.color.G, "G channel did not match expected");
  TEST_ASSERT_EQUAL_MESSAGE(color_test.B, pixel_test.color.B, "B channel did not match expected");
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_setColor_fail_rejectsNull);
  RUN_TEST(test_setColor_success);

  return UNITY_END();
}
