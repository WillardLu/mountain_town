// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <gtest/gtest.h>
#include <mountain_town/string/basic.h>
#include <mountain_town/string/toml.h>

TEST(BasicTests, StrReplace) {
  std::unordered_map<string, string> testdata;
  ReadSTOML("tests/string/testdata/testdata.toml", testdata);
  // 1. 普通测试
  StrReplace(testdata["StrReplace.ori1"], "图片", "image");
  ASSERT_EQ(testdata["StrReplace.ori1"], testdata["StrReplace.result1"]);
  StrReplace(testdata["StrReplace.ori2"], "_somain", "");
  ASSERT_EQ(testdata["StrReplace.ori2"], testdata["StrReplace.result2"]);
  // 2. 边界测试
  StrReplace(testdata["StrReplace.ori3"], "容错", "报错");
  ASSERT_EQ(testdata["StrReplace.ori3"], testdata["StrReplace.result3"]);
  StrReplace(testdata["StrReplace.ori4"], "", "报错");
  ASSERT_EQ(testdata["StrReplace.ori4"], testdata["StrReplace.result4"]);
}

TEST(BasicTests, SplitStr) {
  vector<string> v0 = SplitStr("test,.b,.c", ",.");
  // 1. 普通测试
  ASSERT_EQ(v0.size(), 3);
  ASSERT_EQ(v0[0], "test");
  ASSERT_EQ(v0[1], "b");
  ASSERT_EQ(v0[2], "c");
  // 2. 边界测试
  vector<string> v1 = SplitStr("test,.b,.c", "");
  ASSERT_EQ(v1.size(), 0);
  vector<string> v2 = SplitStr("test,.b,.c", "t");
  ASSERT_EQ(v2.size(), 2);
  ASSERT_EQ(v2[0], "es");
  ASSERT_EQ(v2[1], ",.b,.c");
  vector<string> v3 = SplitStr("test,.b,.c", "c");
  ASSERT_EQ(v3.size(), 1);
  ASSERT_EQ(v3[0], "test,.b,.");
}

TEST(BasicTests, SplitStrRegex) {
  vector<string> v0 = SplitStrRegex("test.b,c.", "[.|,]");
  // 1. 普通测试
  ASSERT_EQ(v0.size(), 3);
  ASSERT_EQ(v0[0], "test");
  ASSERT_EQ(v0[1], "b");
  ASSERT_EQ(v0[2], "c");
  // 2. 边界测试
  vector<string> v1 = SplitStrRegex("test.b,c.", "");
  ASSERT_EQ(v1.size(), 0);
  vector<string> v2 = SplitStrRegex("test,.b,.c", "[t]");
  ASSERT_EQ(v2.size(), 2);
  ASSERT_EQ(v2[0], "es");
  ASSERT_EQ(v2[1], ",.b,.c");
  vector<string> v3 = SplitStrRegex("test,.b,.c", "[c]");
  ASSERT_EQ(v3.size(), 1);
  ASSERT_EQ(v3[0], "test,.b,.");
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
  string a1 = "MNIST";
  ASSERT_EQ(RTrim("MNIST]", "]"), "MNIST");
  ASSERT_EQ(RTrim("3.14 ", " "), "3.14");
  ASSERT_EQ(RTrim("    Hello ", " "), "    Hello");
  ASSERT_EQ(RTrim("string\"\"", "\""), "string");
  //  2. 边界测试
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

TEST(BasicTests, CharArrConvertToString) {
  // 1. 普通测试
  char arr1[] = "Hello";
  ASSERT_EQ(CharArrConvertToString(arr1, 5, 5), "Hello");
  ASSERT_EQ(CharArrConvertToString(arr1, 5, 2, 3), "lo");
  // 2. 错误测试
  ASSERT_EQ(CharArrConvertToString(arr1, 5, 3, 3), "");
}

TEST(BasicTests, ConvertToLowerCase) {
  // 1. 普通测试
  ASSERT_EQ(ConvertToLowerCase("You say goodbye and I say hello."),
            "you say goodbye and i say hello.");
}