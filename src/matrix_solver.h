#pragma once
#include <Eigen/Dense>
#include <vector>

namespace bpm {
Eigen::MatrixXi gauss_mod2(Eigen::MatrixXi A);
std::vector<Eigen::VectorXi> find_basis(Eigen::MatrixXi A);
}
