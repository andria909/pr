#include "matrix_solver.h"
#include <iostream>
namespace bpm {

Eigen::MatrixXi gauss_mod2(Eigen::MatrixXi A) {
  int rows = A.rows();
  int cols = A.cols();
  int r = 0;

  for (int c = 0; c < cols && r < rows; ++c) {
    int pivot = -1;
    for (int i = r; i < rows; ++i) {
      if (A(i, c) != 0) {
        pivot = i;
        break;
      }
    }
    if (pivot == -1)
      continue;

    A.row(r).swap(A.row(pivot));
    for (int i = 0; i < rows; ++i) {
      if (i != r && A(i, c) != 0) {
        A.row(i) = (A.row(i) + A.row(r)).unaryExpr([](int x) { return x % 2; });
      }
    }
    ++r;
  }
  return A;
}

std::vector<Eigen::VectorXi> find_basis(Eigen::MatrixXi A) {
  A = A.transpose().eval();
  A = gauss_mod2(A);

  int rows = A.rows();
  int cols = A.cols();

  std::vector<bool> is_leading(cols, false);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (A(i, j) == 1) {
        is_leading[j] = true;
        break;
      }
    }
  }

  std::vector<Eigen::VectorXi> basis;
  for (int j = 0; j < cols; ++j) {
    if (is_leading[j])
      continue;

    Eigen::VectorXi vec = Eigen::VectorXi::Zero(cols);
    vec(j) = 1;
    for (int i = 0; i < rows; ++i) {
      for (int k = 0; k < cols; ++k) {
        if (A(i, k) == 1) {
          vec(k) = (vec(k) + A(i, j)) % 2;
          break;
        }
      }
    }
    basis.push_back(vec);
  }
  return basis;
}

} // namespace bpm
