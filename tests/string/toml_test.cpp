// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include <gtest/gtest.h>
#include <string/toml.h>

TEST(TOMLTests, ReadSTOML) {
  std::unordered_map<string, string> config;
  ReadSTOML("tests/string/testdata/config.toml", config);
  // 普通测试
  ASSERT_EQ(ReadSTOML("tests/string/testdata/config.toml", config), "");
  ASSERT_EQ(config["MNIST.train_img"], "data/train-images.idx3-ubyte");
  ASSERT_EQ(config["hyper_parameters.LearningRate"], "0.01");
  ASSERT_EQ(config["nerual_network.model1"], "784, 50, 10");
  ASSERT_EQ(config["nerual_network.processing_unit1"],
            "\"FirstAffine\", \"Sigmoid\", \"Affine\", \"SoftmaxWithLoss");
  // 错误测试
  ASSERT_NE(config["MNIST.train_label"], "data/train-images.idx3-ubyte");
  ASSERT_NE(config["hyper_parameters.Learning"], "0.001");
  ASSERT_NE(config["超参数"], "测试");
  ASSERT_NE(ReadSTOML("", config), "");
}