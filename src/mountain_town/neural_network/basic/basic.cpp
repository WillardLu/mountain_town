// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#include "basic.h"

/// @brief sigmoid函数（sigmoid function）
/// @param I 输入（input）
/// @param O 输出（output）
/// @note 本函数只适用于Eigen库的矩阵运算。（This function is only suitable for
/// matrix operations in the Eigen library.）
void EigenSigmoid(MatrixXf &I, MatrixXf &O) {
  O = 1 / (1 + (-I).array().exp());
}
