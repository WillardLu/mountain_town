// @copyright Copyright 2024 Willard Lu
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.
#ifndef MOUNTAIN_TOWN_NEURAL_NETWORK_BASIC_BASIC_H_
#define MOUNTAIN_TOWN_NEURAL_NETWORK_BASIC_BASIC_H_

#include <eigen3/Eigen/Dense>

using Eigen::MatrixXf;

void EigenSigmoid(MatrixXf &I, MatrixXf &O);

#endif  // MOUNTAIN_TOWN_NEURAL_NETWORK_BASIC_BASIC_H_