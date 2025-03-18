#include "utils.h"

cpp_int make_free_of(cpp_int p, cpp_int &n) {
  cpp_int pow = 0;
  while (n % p == 0) {
    ++pow;
    n /= p;
  }
  return pow;
}

cpp_int phi(cpp_int n) {
  cpp_int res = n;
  for (cpp_int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      make_free_of(i, n);
      res -= res / i;
    }
  }
  if (n > 1) {
    res -= res / n;
  }
  return res;
}

cpp_int jacobi(cpp_int a, cpp_int n) {
  a %= n;
  cpp_int result = 1;

  while (a != 0) {
    while (a % 2 == 0) {
      a /= 2;
      cpp_int mod8 = n % 8;
      if (mod8 == 3 || mod8 == 5) {
        result *= -1;
      }
    }
    swap(a, n);
    if (a % 4 == 3 && n % 4 == 3) {
      result *= -1;
    }
    a %= n;
  }
  return (n == 1) ? result : 0;
}

cpp_int gcd(cpp_int a, cpp_int b) {
  while (a > 0) {
    if (b > a) {
      std::swap(a, b);
    }
    a = a % b;
  }
  return b;
}

cpp_int fast_pow(cpp_int base, cpp_int exp, cpp_int mod) {
  cpp_int result = 1;
  base = base % mod;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////////
// AKS functions implmentation

cpp_int poww(cpp_int base, cpp_int exp) {
  cpp_int result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base);
    }
    base = (base * base);
    exp /= 2;
  }
  return result;
}

cpp_int is_perfect_pow(cpp_int n) {
  for (cpp_int a = 2; a * a <= n; ++a) {
    cpp_int l = 1;
    cpp_int r = n;
    cpp_int power;
    while (r - l > 1) {
      cpp_int mid = (l + r) / 2;
      power = poww(a, mid);
      if (power == n) {
        return true;
      } else if (power < n) {
        l = mid;
      } else {
        r = mid;
      }
    }
    if (poww(a, l) == n || poww(a, r) == n) {
      return true;
    }
  }
  return false;
}

cpp_int log2(cpp_int n) {
  if (n <= 0) {
    return 1;
  }

  cpp_int result = 0;
  while (n > 1) {
    n >>= 1;
    ++result;
  }

  if ((poww(2, result)) < n) {
    ++result;
  }

  return result;
}

cpp_int find_smallest_r(cpp_int n) {
  cpp_int log = log2(n);
  cpp_int max_k = pow(log, 2);
  cpp_int r = 1;

  while (true) {
    bool found = true;
    for (cpp_int k = 1; k <= max_k; ++k) {
      if (fast_pow(n, k, r) == 1) {
        found = false;
        break;
      }
    }
    if (found)
      return r;
    ++r;
  }
}

////////////////////////////////////////////////////////////////////////////////////
// Factorization functions implentation

cpp_int formula(cpp_dec_float_50 n) {
  cpp_dec_float_50 res = exp(sqrt(log(n) * log(log(n))));
  return static_cast<cpp_int>(res);
}

std::vector<cpp_int> make_base(cpp_int P, cpp_int n) {
  std::vector<bool> is_prime(static_cast<int>(P) + 1, true);
  std::vector<cpp_int> factor_base;
  is_prime[0] = false;
  is_prime[1] = false;

  for (int i = 2; i <= P; ++i) {
    if (is_prime[i]) {
      for (int j = 2 * i; j <= P; j += i) {
        is_prime[j] = false;
      }
      cpp_int jac = jacobi(n, i);
      if (jac == 1) {

        factor_base.push_back(i);
      } else if (jac == 0) {
        // std::cout << "division " << i << std::endl;
        std::vector<cpp_int> vec;
        vec.push_back(-1);
        return vec;
      }
    }
  }
  return factor_base;
}

void decomposition(std::unordered_map<cpp_int, cpp_int> &f,
                   std::unordered_map<cpp_int, std::vector<bool>> &vec_fact,
                   std::vector<cpp_int> &S) {
  for (int i = 0; i < S.size(); ++i) {
    for (auto &[x, f_x] : f) {
      cpp_int pow = make_free_of(S[i], f_x);
      vec_fact[x][i] = static_cast<bool>(pow % 2);
    }
  }
}

int find_pivot_row(const std::vector<std::vector<bool>> &A, int col,
                   int start_row) {
  for (int i = start_row; i < static_cast<int>(A.size()); ++i) {
    if (A[i][col]) {
      return i;
    }
  }
  return -1;
}

void xor_rows(std::vector<bool> &target, const std::vector<bool> &source) {
  for (int j = 0; j < target.size(); ++j) {
    target[j] = target[j] ^ source[j];
  }
}

int find_pivot_col(const std::vector<std::vector<bool>> &A, int row) {
  for (int j = 0; j < A[row].size(); ++j) {
    if (A[row][j]) {
      return j;
    }
  }
  return -1;
}

void gauss(std::vector<std::vector<bool>> &A) {
  const int rows = A.size();
  if (rows == 0)
    return;
  const int cols = A[0].size();
  int pivot_row = 0;

  for (int col = 0; col < cols && pivot_row < rows; ++col) {
    int pivot = find_pivot_row(A, col, pivot_row);
    if (pivot == -1) {
      continue;
    }

    std::swap(A[pivot_row], A[pivot]);

    for (int i = pivot_row + 1; i < rows; ++i) {
      if (A[i][col]) {
        xor_rows(A[i], A[pivot_row]);
      }
    }
    pivot_row++;
  }

  for (int i = rows - 1; i >= 0; --i) {
    int lead_col = find_pivot_col(A, i);
    if (lead_col == -1) {
      continue;
    }

    for (int k = i - 1; k >= 0; --k) {
      if (A[k][lead_col]) {
        xor_rows(A[k], A[i]);
      }
    }
  }
}

std::vector<std::vector<bool>>
transpose(const std::vector<std::vector<bool>> &A) {
  if (A.empty())
    return {};
  int rows = A.size();
  int cols = A[0].size();
  std::vector<std::vector<bool>> result(cols, std::vector<bool>(rows));
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      result[j][i] = A[i][j];
    }
  }
  return result;
}

std::vector<int> find_leading_columns(const std::vector<std::vector<bool>> &A) {
  std::vector<int> leading;
  if (A.empty())
    return leading;
  const int cols = A[0].size();
  leading.resize(cols, -1);
  for (int i = 0; i < A.size(); ++i) {
    for (int j = 0; j < cols; ++j) {
      if (A[i][j]) {
        leading[j] = static_cast<int>(i);
        break;
      }
    }
  }
  return leading;
}

std::vector<bool>
create_basis_vector(int col, const std::vector<int> &leading,
                    const std::vector<std::vector<bool>> &At) {
  std::vector<bool> vec(leading.size(), false);
  vec[col] = 1;
  for (int k = 0; k < leading.size(); ++k) {
    int lead_row = leading[k];
    if (lead_row != -1 && At[lead_row][col]) {
      vec[k] = true;
    }
  }
  return vec;
}

std::vector<std::vector<bool>> find_basis(std::vector<std::vector<bool>> &A) {
  if (A.empty() || A[0].empty()) {
    return {};
  }
  std::vector<std::vector<bool>> At = transpose(A);
  gauss(At);
  const std::vector<int> leading = find_leading_columns(At);
  std::vector<std::vector<bool>> basis;
  for (int j = 0; j < leading.size(); ++j) {
    if (leading[j] == -1) {
      basis.push_back(create_basis_vector(j, leading, At));
    }
  }
  return basis;
}
cpp_int my_sqrt(std::vector<cpp_int> &S, cpp_int n) {
  cpp_int sqrt_n = 1;
  for (auto &prime : S) {
    cpp_int pow = make_free_of(prime, n);
    sqrt_n *= poww(prime, pow / 2);
  }
  return sqrt_n;
}

////////////////////////////////////////////////////////////////////////////////////
// Random implmentation

Random::Random(int seed) : generator_(seed) {}

cpp_int Random::uniform(cpp_int a, cpp_int b) {
  if (a > b) {
    std::swap(a, b);
  }

  cpp_int range = b - a + 1;
  cpp_int result = get_random(range);
  return a + result;
}

cpp_int Random::get_random(const cpp_int &range) {
  cpp_int result = 0;
  cpp_int base = 1;
  cpp_int max_val = range;

  std::uniform_int_distribution<uint32_t> distrib(0, UINT32_MAX);

  while (max_val > 0) {
    uint32_t random_part = distrib(generator_);
    result += static_cast<cpp_int>(random_part) * base;
    base *= (UINT32_MAX + 1ULL);
    max_val /= (UINT32_MAX + 1ULL);
  }

  return result % range;
}