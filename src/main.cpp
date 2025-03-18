#include "utils.h"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace boost::multiprecision;

namespace {

enum class TestStatus : int {
  Prime,
  Composite,
  ProbablyPrime,
  ProbablyComposite

};

TestStatus fermat_test(const cpp_int &n, const cpp_int &k, Random &ferma) {
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;
  for (cpp_int i = 0; i < k; ++i) {
    cpp_int a = ferma.uniform(2, n - 4);
    cpp_int x = fast_pow(a, n - 1, n);
    if (x != 1) {
      return TestStatus::Composite;
    }
  }
  return TestStatus::ProbablyPrime;
}

TestStatus solovay_shtressen_test(const cpp_int &n, const cpp_int &k,
                                  Random &solovay) {
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;

  for (cpp_int i = 0; i < k; ++i) {
    cpp_int a = solovay.uniform(2, n - 4);
    if (gcd(a, n) > 1) {
      return TestStatus::Composite;
    }
    if ((fast_pow(a, (n - 1) / 2, n) + n) % n != (jacobi(a, n) + n) % n) {
      return TestStatus::Composite;
    }
  }
  return TestStatus::ProbablyPrime;
}

TestStatus miller_rabin_test(const cpp_int &n, const cpp_int &k,
                             Random &miller) {
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;

  cpp_int t = n - 1;
  cpp_int s = make_free_of(2, t);
  for (cpp_int i = 0; i < k; ++i) {
    cpp_int a = miller.uniform(2, n - 4);
    cpp_int x = fast_pow(a, t, n);

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

TestStatus aks_test(cpp_int n) {
  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;
  if (is_perfect_pow(n))
    return TestStatus::Composite;

  cpp_int r = find_smallest_r(n);
  for (cpp_int a = 2; a <= r; ++a) {
    if (!(gcd(a, n) == 1 || gcd(a, n) == n))
      return TestStatus::Composite;
  }
  if (n <= r)
    return TestStatus::ProbablyPrime;
  cpp_int limit = sqrt(phi(r)) * log2(n);
  for (cpp_int a = 1; a <= limit; ++a) {
    if (fast_pow(a, n - 1, n) != 1)
      return TestStatus::Composite;
  }
  return TestStatus::ProbablyPrime;
}

TestStatus factorization_test(const cpp_int &n) {

  if (n == 1) {
    return TestStatus::Composite;
  }
  if (n < 1)
    throw std::invalid_argument("Аргументы должны быть >= 1");
  if (n <= 3)
    return TestStatus::Prime;

  std::unordered_map<cpp_int, cpp_int> f;
  std::unordered_map<cpp_int, std::vector<bool>> vec_fact;

  cpp_int T = (sqrt(n) / 1 == sqrt(n)) ? sqrt(n) : sqrt(n) / 1 + 1;

  cpp_int A = formula(static_cast<cpp_dec_float_50>(n));

  cpp_int P = static_cast<int>(sqrt(A)) * 4;

  std::vector<cpp_int> S = make_base(P, n);
  if (S[0] == -1) {
    return TestStatus::Composite;
  }

  for (cpp_int i = 0; i < A; ++i) {
    cpp_int x = T + i;
    f[x] = x * x - n;
    vec_fact[x].resize(S.size());
  }
  std::unordered_map<cpp_int, cpp_int> new_f = f;
  decomposition(f, vec_fact, S);
  std::vector<std::vector<bool>> Matrix;

  std::unordered_map<int, cpp_int> mapp;
  int num_ones = 0;
  for (auto &[x, f_x] : f) {
    if (f[x] == 1) {
      mapp[num_ones] = x;
      Matrix.push_back(vec_fact[x]);
      ++num_ones;
    }
  }

  std::vector<std::vector<bool>> solution = find_basis(Matrix);

  for (int i = 0; i < solution.size(); ++i) {
    cpp_int x_value = 1;
    cpp_int y_value = 1;
    for (int j = 0; j < num_ones; ++j) {
      if (solution[i][j] == 1) {
        x_value *= mapp[j];
        y_value *= new_f[mapp[j]];
      }
    }
    y_value = my_sqrt(S, y_value);

    cpp_int summa = gcd(x_value + y_value, n);
    cpp_int raznost = gcd(x_value - y_value, n);
    if (!((summa == 1 || summa == n) || (raznost == 1 || raznost == n))) {
      return TestStatus::Composite;
    }
  }

  return TestStatus::ProbablyPrime;
}
}
