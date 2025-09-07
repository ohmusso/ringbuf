#include <gtest/gtest.h>

extern "C"
{
#include "ringbuf.h"
}

class RingBufTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    v_RingBuf_init();
  }

  virtual void TearDown()
  {
  }
};

TEST_F(RingBufTest, push_pop)
{
  int i;
  size_t ret;
  uint8_t input_data[5] = {1, 2, 3, 4, 5};
  uint8_t output_pop_data[5] = {0, 0, 0, 0, 0};
  const uint8_t output_ringbuf[10] = {1, 2, 3, 4, 5, 0, 0, 0, 0, 0};

  ret = v_RingBuf_push(input_data, 5);
  EXPECT_EQ(ret, 5);
  EXPECT_EQ(5, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  for (i = 0; i < 10; i++)
  {
    EXPECT_EQ(output_ringbuf[i], ringBuf.buf[i]);
  }

  ret = v_RingBuf_pop(output_pop_data, 5);
  EXPECT_EQ(ret, 5);
  EXPECT_EQ(5, ringBuf.wPos);
  EXPECT_EQ(5, ringBuf.rPos);
  for (i = 0; i < 5; i++)
  {
    EXPECT_EQ(output_pop_data[i], ringBuf.buf[i]);
  }
}

TEST_F(RingBufTest, push_exceed)
{
  int i;
  size_t ret;
  uint8_t input_data_01[5] = {1, 2, 3, 4, 5};
  uint8_t input_data_02[5] = {6, 7, 8, 9, 10};
  uint8_t input_data_03[5] = {11, 12, 13, 14, 15};
  const uint8_t output_ringbuf[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  ret = v_RingBuf_push(input_data_01, 5);
  EXPECT_EQ(ret, 5);
  EXPECT_EQ(5, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  ret = v_RingBuf_push(input_data_02, 5);
  EXPECT_EQ(ret, 5);
  EXPECT_EQ(0, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  for (i = 0; i < 10; i++)
  {
    EXPECT_EQ(output_ringbuf[i], ringBuf.buf[i]);
  }

  ret = v_RingBuf_push(input_data_03, 0);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(0, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  ret = v_RingBuf_push(input_data_03, 1);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(0, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  ret = v_RingBuf_push(input_data_03, 5);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(0, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
}

TEST_F(RingBufTest, pop_empty)
{
  int i;
  size_t ret;
  uint8_t input_data[5] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
  const uint8_t output_ringbuf[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  ret = v_RingBuf_pop(input_data, 5);
  EXPECT_EQ(ret, 0);
  EXPECT_EQ(0, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  for (i = 0; i < 10; i++)
  {
    EXPECT_EQ(output_ringbuf[i], ringBuf.buf[i]);
  }
}

TEST_F(RingBufTest, push_pop_push)
{
  int i;
  size_t ret;
  uint8_t input_data_01[4] = {1, 2, 3, 4};
  uint8_t input_data_02[4] = {5, 6, 7, 8};
  uint8_t input_data_03[4] = {9, 10, 11, 12};
  uint8_t output_data_01[4] = {0, 0, 0, 0};
  const uint8_t output_ringbuf_01[10] = {1, 2, 3, 4, 5, 6, 7, 8, 0, 0};
  const uint8_t output_ringbuf_02[10] = {11, 12, 3, 4, 5, 6, 7, 8, 9, 10};

  ret = v_RingBuf_push(input_data_01, 4);
  EXPECT_EQ(ret, 4);
  EXPECT_EQ(4, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  ret = v_RingBuf_push(input_data_02, 4);
  EXPECT_EQ(ret, 4);
  EXPECT_EQ(8, ringBuf.wPos);
  EXPECT_EQ(0, ringBuf.rPos);
  for (i = 0; i < 10; i++)
  {
    EXPECT_EQ(output_ringbuf_01[i], ringBuf.buf[i]);
  }

  ret = v_RingBuf_pop(output_data_01, 4);
  EXPECT_EQ(ret, 4);
  EXPECT_EQ(8, ringBuf.wPos);
  EXPECT_EQ(4, ringBuf.rPos);
  ret = v_RingBuf_push(input_data_03, 4);
  EXPECT_EQ(ret, 4);
  EXPECT_EQ(2, ringBuf.wPos);
  EXPECT_EQ(4, ringBuf.rPos);
  for (i = 0; i < 10; i++)
  {
    EXPECT_EQ(output_ringbuf_02[i], ringBuf.buf[i]);
  }
}