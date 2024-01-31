// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <gtest/gtest.h>
#include <string/basic.h>

TEST(BasicTests, StrReplace) {
  ASSERT_EQ("", "");
}

TEST(BasicTests, SplitStr) {
  ASSERT_EQ("", "");
}

TEST(BasicTests, LTrim) {
  // 1. 普通测试
  ASSERT_EQ(LTrim(" 3.14", " "), "3.14");
  ASSERT_EQ(LTrim("    Hello ", " "), "Hello ");
  ASSERT_EQ(LTrim("\"\"string", "\""), "string");
  // 2. 边界测试
  ASSERT_EQ(LTrim("3.14", " "), "3.14");
  ASSERT_EQ(LTrim("", " "), "");
  ASSERT_EQ(LTrim(" 3.14", ""), " 3.14");
}

TEST(BasicTests, RTrim) {
  // 1. 普通测试
  ASSERT_EQ(RTrim("3.14 ", " "), "3.14");
  ASSERT_EQ(RTrim("    Hello ", " "), "    Hello");
  ASSERT_EQ(RTrim("string\"\"", "\""), "string");
  // 2. 边界测试
  ASSERT_EQ(RTrim("3.14", " "), "3.14");
  ASSERT_EQ(RTrim("", " "), "");
  ASSERT_EQ(RTrim(" 3.14", ""), " 3.14");
}

TEST(BasicTests, Trim) {
  // 1. 普通测试
  ASSERT_EQ(Trim("  3.14 ", " "), "3.14");
  ASSERT_EQ(Trim("    Hello ", " "), "Hello");
  ASSERT_EQ(Trim("\"string\"\"", "\""), "string");
  // 2. 边界测试
  ASSERT_EQ(Trim("3.14", " "), "3.14");
  ASSERT_EQ(Trim("", " "), "");
  ASSERT_EQ(Trim(" 3.14", ""), " 3.14");
}