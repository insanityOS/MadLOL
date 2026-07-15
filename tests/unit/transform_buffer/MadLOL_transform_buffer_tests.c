#include <stdlib.h>
#include <string.h>
#include "MadLOL_types.h"
#define MADLOL_CREATE_REFERENCE_PIXEL
#include "MadLOL_frame_buffer.h"
#include "MadLOL_transform_buffer.h"
#include "MockMadLOL_frame_buffer.h"
#include "unity.h"

#define TEST_WIDTH 4
#define TEST_HEIGHT 3

static uint32_t buffer_count = 0;

MadLOL_Status_t callback_MadLOL_setColor(MadLOL_Pixel* pixel, MadLOL_Color color, int NumCalls) {
  pixel->color = color;

  return LOL_SUCCESS;
}

void setUp(void) {
  MockMadLOL_frame_buffer_Init();
}

void tearDown(void) {
  verifyTest();
  MockMadLOL_frame_buffer_Init();
}

void verifyTest(void) {
  MockMadLOL_frame_buffer_Verify();
  if (buffer_count) {
    TEST_FAIL_MESSAGE("There are un-freed buffers... We don't take kindly to leakers, 'round these parts...");
  }
}

const MadLOL_Pixel pixelBuffer_testBase[TEST_WIDTH * TEST_HEIGHT] = {
    {.color = {.R = 0x0, .G = 0x0, .B = 0x0}}, {.color = {.R = 0x1, .G = 0x1, .B = 0x1}},
    {.color = {.R = 0x2, .G = 0x2, .B = 0x2}}, {.color = {.R = 0x3, .G = 0x3, .B = 0x3}},
    {.color = {.R = 0x4, .G = 0x4, .B = 0x4}}, {.color = {.R = 0x5, .G = 0x5, .B = 0x5}},
    {.color = {.R = 0x6, .G = 0x6, .B = 0x6}}, {.color = {.R = 0x7, .G = 0x7, .B = 0x7}},
    {.color = {.R = 0x8, .G = 0x8, .B = 0x8}}, {.color = {.R = 0x9, .G = 0x9, .B = 0x9}},
    {.color = {.R = 0xa, .G = 0xa, .B = 0xa}}, {.color = {.R = 0xb, .G = 0xb, .B = 0xb}}};

const MadLOL_Pixel pixelBuffer_expectedRotate90[TEST_WIDTH * TEST_HEIGHT] = {
    {.color = {.R = 0x8, .G = 0x8, .B = 0x8}}, {.color = {.R = 0x4, .G = 0x4, .B = 0x4}},
    {.color = {.R = 0x0, .G = 0x0, .B = 0x0}}, {.color = {.R = 0x9, .G = 0x9, .B = 0x9}},
    {.color = {.R = 0x5, .G = 0x5, .B = 0x5}}, {.color = {.R = 0x1, .G = 0x1, .B = 0x1}},
    {.color = {.R = 0xa, .G = 0xa, .B = 0xa}}, {.color = {.R = 0x6, .G = 0x6, .B = 0x6}},
    {.color = {.R = 0x2, .G = 0x2, .B = 0x2}}, {.color = {.R = 0xb, .G = 0xb, .B = 0xb}},
    {.color = {.R = 0x7, .G = 0x7, .B = 0x7}}, {.color = {.R = 0x3, .G = 0x3, .B = 0x3}}};

const MadLOL_Pixel pixelBuffer_expectedRotate180[TEST_WIDTH * TEST_HEIGHT] = {
    {.color = {.R = 0xb, .G = 0xb, .B = 0xb}}, {.color = {.R = 0xa, .G = 0xa, .B = 0xa}},
    {.color = {.R = 0x9, .G = 0x9, .B = 0x9}}, {.color = {.R = 0x8, .G = 0x8, .B = 0x8}},
    {.color = {.R = 0x7, .G = 0x7, .B = 0x7}}, {.color = {.R = 0x6, .G = 0x6, .B = 0x6}},
    {.color = {.R = 0x5, .G = 0x5, .B = 0x5}}, {.color = {.R = 0x4, .G = 0x4, .B = 0x4}},
    {.color = {.R = 0x3, .G = 0x3, .B = 0x3}}, {.color = {.R = 0x2, .G = 0x2, .B = 0x2}},
    {.color = {.R = 0x1, .G = 0x1, .B = 0x1}}, {.color = {.R = 0x0, .G = 0x0, .B = 0x0}}};

const MadLOL_Pixel pixelBuffer_expectedRotate270[TEST_WIDTH * TEST_HEIGHT] = {
    {.color = {.R = 0x3, .G = 0x3, .B = 0x3}}, {.color = {.R = 0x7, .G = 0x7, .B = 0x7}},
    {.color = {.R = 0xb, .G = 0xb, .B = 0xb}}, {.color = {.R = 0x2, .G = 0x2, .B = 0x2}},
    {.color = {.R = 0x6, .G = 0x6, .B = 0x6}}, {.color = {.R = 0xa, .G = 0xa, .B = 0xa}},
    {.color = {.R = 0x1, .G = 0x1, .B = 0x1}}, {.color = {.R = 0x5, .G = 0x5, .B = 0x5}},
    {.color = {.R = 0x9, .G = 0x9, .B = 0x9}}, {.color = {.R = 0x0, .G = 0x0, .B = 0x0}},
    {.color = {.R = 0x4, .G = 0x4, .B = 0x4}}, {.color = {.R = 0x8, .G = 0x8, .B = 0x8}}};

const MadLOL_Size size_horizontal = {.width = TEST_WIDTH, .height = TEST_HEIGHT};
const MadLOL_Size size_vertical = {.width = TEST_HEIGHT, .height = TEST_WIDTH};

// Allocates memory for and copy-initializes destination parameter
void helper_makeBuffer(MadLOL_FrameBuffer* dst, const MadLOL_Pixel* const src, const MadLOL_Size size) {
  MadLOL_Pixel* frame_buffer = (MadLOL_Pixel*)malloc(sizeof(MadLOL_Pixel) * size.height * size.width);

  if (!frame_buffer) {
    printf("Out of memory!");
    TEST_ABORT();
  }

  buffer_count++;

  dst->frame = frame_buffer;
  dst->size = size;
  memcpy(dst->frame, src, sizeof(MadLOL_Pixel) * size.width * size.height);
}

void helper_assertFrameEqual(const MadLOL_Pixel* actual, const MadLOL_Pixel* const expected) {
  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected, actual, sizeof(MadLOL_Pixel) * TEST_HEIGHT * TEST_WIDTH,
                                       "Pixel Array does not match expected");
}

void helper_deleteBuffer(MadLOL_FrameBuffer* fb) {
  if (!fb->frame) {
    TEST_FAIL_MESSAGE("Are you fucking kidding me? NO DOUBLE FREES, MORON!");
  }

  free(fb->frame);
  fb->frame = NULL;

  fb->size = (MadLOL_Size){.width = 0, .height = 0};

  buffer_count--;
}

void test_MadLOL_rotateBuffer_copy_success_90(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  for (uint16_t i = 0; i < TEST_WIDTH * TEST_HEIGHT; i++)
    MadLOL_setColor_ExpectAnyArgsAndReturn(LOL_SUCCESS);

  MadLOL_setColor_AddCallback(&callback_MadLOL_setColor);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_assertFrameEqual(frame_buffer_actual, pixelBuffer_expectedRotate90);

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_success_180(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_180;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_horizontal;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  for (uint16_t i = 0; i < TEST_WIDTH * TEST_HEIGHT; i++)
    MadLOL_setColor_ExpectAnyArgsAndReturn(LOL_SUCCESS);

  MadLOL_setColor_AddCallback(&callback_MadLOL_setColor);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_assertFrameEqual(frame_buffer_actual, pixelBuffer_expectedRotate180);

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_success_270(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_SUCCESS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_270;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  for (uint16_t i = 0; i < TEST_WIDTH * TEST_HEIGHT; i++)
    MadLOL_setColor_ExpectAnyArgsAndReturn(LOL_SUCCESS);

  MadLOL_setColor_AddCallback(&callback_MadLOL_setColor);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_assertFrameEqual(frame_buffer_actual, pixelBuffer_expectedRotate270);

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_nullPointer_inner_90(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_INNERFAIL | LOL_NULLPTR;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  MadLOL_setColor_ExpectAnyArgsAndReturn(LOL_NULLPTR);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_nullPointer_inner_180(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_INNERFAIL | LOL_NULLPTR;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_180;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_horizontal;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  MadLOL_setColor_ExpectAnyArgsAndReturn(LOL_NULLPTR);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_nullPointer_inner_270(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_INNERFAIL | LOL_NULLPTR;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_270;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  MadLOL_setColor_ExpectAnyArgsAndReturn(LOL_NULLPTR);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_nullPointer_src(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_NULLPTR;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_src.frame = NULL;
  fb_src.size = size_horizontal;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");
}

void test_MadLOL_rotateBuffer_copy_nullPointer_dst(void) {
  MadLOL_Status_t status_expected = LOL_NULLPTR;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = NULL;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_src_width(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_src.size.width = 0;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_src_height(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_src.size.height = 0;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_dst_width_90(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.width = TEST_WIDTH;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_dst_height_90(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_90;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.height = TEST_HEIGHT;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_dst_width_180(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_180;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_horizontal;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.width = TEST_HEIGHT;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_dst_height_180(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_180;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_horizontal;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.height = TEST_WIDTH;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_dst_width_270(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_270;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.width = TEST_WIDTH;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badSize_dst_height_270(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADBOUNDS;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_270;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.height = TEST_HEIGHT;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badRotation_0(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADPARAM;

  MadLOL_Rotate_t rotation_test = 0;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.height = TEST_WIDTH;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

void test_MadLOL_rotateBuffer_copy_badRotation_high(void) {
  MadLOL_Pixel frame_buffer_actual[TEST_WIDTH * TEST_HEIGHT] = {0};
  MadLOL_Status_t status_expected = LOL_BADPARAM;

  MadLOL_Rotate_t rotation_test = LOL_DEGREES_270 + 1;

  MadLOL_FrameBuffer fb_src, fb_dst;

  fb_dst.size = size_vertical;
  fb_dst.frame = frame_buffer_actual;

  helper_makeBuffer(&fb_src, pixelBuffer_testBase, size_horizontal);

  fb_dst.size.height = TEST_WIDTH;

  TEST_ASSERT_EQUAL_MESSAGE(status_expected, MadLOL_rotateBuffer_copy(fb_src, fb_dst, rotation_test),
                            "Incorrect return status");

  helper_deleteBuffer(&fb_src);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_MadLOL_rotateBuffer_copy_success_90);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_success_180);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_success_270);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_nullPointer_inner_90);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_nullPointer_inner_180);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_nullPointer_inner_270);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_nullPointer_src);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_nullPointer_dst);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_src_width);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_src_height);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_dst_width_90);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_dst_height_90);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_dst_width_180);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_dst_height_180);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_dst_width_270);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badSize_dst_height_270);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badRotation_0);
  RUN_TEST(test_MadLOL_rotateBuffer_copy_badRotation_high);

  return UNITY_END();
}
