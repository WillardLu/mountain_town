// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <gtest/gtest.h>
#include <mountain_town/math/random.h>

TEST(MathTests, BetterRand) {
  int rn[10] = {0};
  BetterRand(rn, 10, 1, 100);
  for (int i = 0; i < 10; i++) {
    EXPECT_GE(rn[i], 1);
    EXPECT_LE(rn[i], 100);
  }
  BetterRand(rn, 10, -784, -20);
  for (int i = 0; i < 10; i++) {
    EXPECT_GE(rn[i], -784);
    EXPECT_LE(rn[i], -20);
  }
}

TEST(MathTests, NormalDistr) {
  float rn[10000] = {0};
  NormalDistr(rn, 10000, 0.0, 1.0);
  float sum = 0;
  for (int i = 0; i < 10000; i++) {
    sum += rn[i];
  }
  // 注意，这里的测试并不严谨。
  // 当数据量小的时候，随机数的均值与设定的均值会有较大偏差，随着数据量增大，
  // 这个偏差会缩小，但还是有可能出现较大偏差的情况。
  EXPECT_NEAR(sum / 10000.0, 0.0, 0.05);
}