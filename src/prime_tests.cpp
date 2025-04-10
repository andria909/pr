#include "fft.h"
#include "longnum.h"
#include "math.h"
#include "matrix_solver.h"
#include "random.h"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace bpm {

enum class TestStatus : int {
  Prime,
  Composite,
  ProbablyPrime,
  ProbablyComposite
};

TestStatus ferma_test(const LongInt &n, const LongInt &k) {
  Random ferma(true);
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::ProbablyPrime;
  for (LongInt i = 0; i < k; ++i) {
    LongInt a = ferma.uniform(2, n - 2);
    LongInt x = fast_pow(a, n - 1, n);
    if (x != 1) {
      return TestStatus::Composite;
    }
  }
  return TestStatus::ProbablyPrime;
}

TestStatus solovay_shtressen_test(const LongInt &n, const LongInt &k) {
  Random solovay(true);
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::ProbablyPrime;

  for (LongInt i = 0; i < k; ++i) {
    LongInt a = solovay.uniform(2, n - 4);
    if (gcd(a, n) > 1) {
      return TestStatus::Composite;
    }
    if ((fast_pow(a, (n - 1) / 2, n) + n) % n != (jacobi(a, n) + n) % n) {
      return TestStatus::Composite;
    }
  }
  return TestStatus::ProbablyPrime;
}

TestStatus miller_rabin_test(const LongInt &n, const LongInt &k) {
  Random miller(true);
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::ProbablyPrime;

  LongInt t = n - 1;
  LongInt s = make_free_of(2, t);
  for (LongInt i = 0; i < k; ++i) {
    LongInt a = miller.uniform(2, n - 4);
    LongInt x = fast_pow(a, t, n);

    if (x != 1 && x != n - 1) {
      bool fl = true;
      for (int j = 0; j < s && fl; ++j) {
        x = (x * x) % n;
        if (x == 1)
          return TestStatus::Composite;
        if (x == n - 1)
          fl = false;
      }
      if (fl)
        return TestStatus::Composite;
    }
  }
  return TestStatus::ProbablyPrime;
}

TestStatus aks_test(LongInt n) {
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;
  if (is_perfect_pow(n))
    return TestStatus::Composite;

  LongInt r = find_smallest_ord(n);
  for (LongInt a = 2; a <= r; ++a) {
    if (!(gcd(a, n) == 1 || gcd(a, n) == n))
      return TestStatus::Composite;
  }
  if (n <= r)
    return TestStatus::Prime;
  LongInt limit = sqrt(phi(r)) * log2(n);
  for (LongInt a = 1; a <= limit; ++a) {
    if (!check_congruence(a, n, r))
      return TestStatus::Composite;
  }
  return TestStatus::Prime;
}

TestStatus factorization_test(const LongInt &n) {
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;

  std::vector<LongInt> args = compute_args(static_cast<LongDouble>(n));

  LongInt T = args[0];

  LongInt A = args[1];

  LongInt P = args[2];

  std::vector<LongInt> S = make_base(P, n);
  if (S[0] == -1) {
    return TestStatus::Composite;
  }
  
  std::unordered_map<LongInt, LongInt> f;
  std::unordered_map<LongInt, std::vector<bool>> vec_fact;

  creating_objects(f, vec_fact, A, T, n, S.size());


  std::unordered_map<LongInt, LongInt> new_f = f;
  decomposition(f, vec_fact, S);
  std::vector<int> Matrix;
  std::unordered_map<int, LongInt> mapp;
  int num_ones = 0;
  for (auto &[x, f_x] : f) {
    if (f[x] == 1) {
      mapp[num_ones] = x;
      for (int i = 0; i < vec_fact[x].size(); ++i) {
        Matrix.push_back(vec_fact[x][i]);
      }
      ++num_ones;
    }
  }

  Eigen::Map<
      Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>>
      mat(Matrix.data(), num_ones, Matrix.size() / num_ones);
  std::vector<Eigen::VectorXi> solution = find_basis(mat);
  for (int i = 0; i < solution.size(); ++i) {
    LongInt x_value = 1;
    LongInt y_value = 1;
    for (int j = 0; j < num_ones; ++j) {
      if (solution[i][j] == 1) {
        x_value *= mapp[j];
        y_value *= new_f[mapp[j]];
      }
    }
    y_value = my_sqrt(S, y_value);

    LongInt d_1 = gcd(x_value + y_value, n);
    LongInt d_2 = gcd(x_value - y_value, n);
    if (!((d_1 == 1 || d_1 == n) || (d_2 == 1 || d_2 == n))) {
      return TestStatus::Composite;
    }
  }

  return TestStatus::Prime;
}
} // namespace bpm
