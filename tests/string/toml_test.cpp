// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <gtest/gtest.h>
#include <mountain_town/string/toml.h>

TEST(TOMLTests, ReadSTOML) {
  std::unordered_map<string, string> config;
  string err = ReadSTOML("tests/string/testdata/config.toml", config);
  // 普通测试
  ASSERT_EQ(err, "");
  ASSERT_EQ(config["MNIST.train_img"], "data/train-images.idx3-ubyte");
  ASSERT_EQ(config["hyper_parameters.LearningRate"], "0.01");
  ASSERT_EQ(config["nerual_network.struct"],
            "\"Affine\", \"Sigmoid\", \"Affine\", \"SoftmaxWithLoss\"");
  ASSERT_EQ(config["nerual_network.struct1"],
            "\"Affine\",\"Sigmoid\",\"Affine\",\"Affine\",\"Sigmoid\","
            "\"Affine\",\"SoftmaxWithLoss\"");
  vector<string> arr;
  ReadSTOMLArr(config["nerual_network.struct1"], arr);
  ASSERT_EQ(arr.size(), 7);
  ASSERT_EQ(arr[0], "Affine");
  ASSERT_EQ(arr[6], "SoftmaxWithLoss");
  // 错误测试
  ASSERT_NE(config["MNIST.train_label"], "data/train-images.idx3-ubyte");
  ASSERT_NE(config["hyper_parameters.Learning"], "0.001");
  ASSERT_NE(config["超参数"], "测试");
  ASSERT_NE(ReadSTOML("", config), "");

  std::unordered_map<string, string> config1;
  ReadSTOML("tests/string/testdata/config1.toml", config1);
  string str1 = "\"MatMul+MatMul:3\", \"MatMul:7\", \"SoftmaxWithLoss\"";
  ASSERT_EQ(config1["neural_network.struct"], str1);
}