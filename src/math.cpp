#include "math.h"

namespace bpm {

LongInt make_free_of(LongInt p, LongInt &n) {
  LongInt pow = 0;
  while (n % p == 0) {
    ++pow;
    n /= p;
  }
  return pow;
}

LongInt phi(LongInt n) {
  LongInt res = n;
  for (LongInt i = 2; i * i <= n; ++i) {
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

LongInt jacobi(LongInt a, LongInt n) {
  a %= n;
  LongInt result = 1;

  while (a != 0) {
    while (a % 2 == 0) {
      a /= 2;
      LongInt mod8 = n % 8;
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

LongInt gcd(LongInt a, LongInt b) {
  while (a > 0) {
    if (b > a) {
      std::swap(a, b);
    }
    a = a % b;
  }
  return b;
}

LongInt fast_pow(LongInt base, LongInt exp, LongInt mod) {
  LongInt result = 1;
  base = base % mod;

  while (exp > 0) {
    if ((exp & 1) == 1) {
      result = (result * base) % mod;
    }

    base = (base * base) % mod;
    exp >>= 1;
  }

  return result;
}

LongInt poww(LongInt base, LongInt exp) {
  LongInt result = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      result = (result * base);
    }
    base = (base * base);
    exp /= 2;
  }
  return result;
}

bool is_perfect_pow(LongInt n) {
  if (n < 2)
    return false;

  LongInt max_b = static_cast<LongInt>(log2(n)) + 1;

  for (int b = 2; b <= max_b; ++b) {
    LongInt low = 2;
    LongInt high = n;

    while (low <= high) {
      LongInt mid = (low + high) / 2;
      LongInt power = poww(mid, b);

      if (power > n) {
        high = mid - 1;
      } else if (power < n) {
        low = mid + 1;
      } else {
        return true;
      }
    }
  }
  return false;
}

LongInt log2(LongInt n) {
  if (n <= 0) {
    return 1;
  }

  LongInt result = 0;
  while (n > 1) {
    n >>= 1;
    ++result;
  }

  if ((poww(2, result)) < n) {
    ++result;
  }

  return result;
}

LongInt find_smallest_ord(LongInt n) {
  LongInt log = log2(n);
  LongInt max_k = pow(log, 2);
  LongInt r = 1;

  while (true) {
    bool found = true;
    for (LongInt k = 1; k <= max_k; ++k) {
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

std::vector<LongInt> compute_args(LongDouble n) {
  std::vector<LongInt> args;
  args.push_back(static_cast<LongInt>(sqrt(n)));
  LongDouble A = exp(sqrt(log(n) * log(log(n))));
  args.push_back(static_cast<LongInt>(A));
  args.push_back(static_cast<LongInt>(sqrt(args[1]) * 4 + 4));
  return args;
}

void creating_objects(std::unordered_map<LongInt, LongInt> &f,
                      std::unordered_map<LongInt, std::vector<bool>> &vec_fact,
                      LongInt A, LongInt T, LongInt n, int m) {
  for (LongInt i = 0; i < A; ++i) {
    LongInt x = T + i;
    f[x] = x * x - n;
    vec_fact[x].resize(m);
  }
}

std::vector<LongInt> make_base(LongInt P, LongInt n) {
  std::vector<bool> is_prime(static_cast<int>(P) + 1, true);
  std::vector<LongInt> factor_base;
  is_prime[0] = false;
  is_prime[1] = false;

  for (int i = 2; i <= P; ++i) {
    if (is_prime[i]) {
      for (int j = 2 * i; j <= P; j += i) {
        is_prime[j] = false;
      }
      LongInt jac = jacobi(n, i);
      if (jac == 1) {

        factor_base.push_back(i);
      } else if (jac == 0) {
        std::vector<LongInt> vec;
        vec.push_back(-1);
        return vec;
      }
    }
  }
  return factor_base;
}

void decomposition(std::unordered_map<LongInt, LongInt> &f,
                   std::unordered_map<LongInt, std::vector<bool>> &vec_fact,
                   std::vector<LongInt> &S) {
  for (int i = 0; i < S.size(); ++i) {
    for (auto &[x, f_x] : f) {
      LongInt pow = make_free_of(S[i], f_x);
      vec_fact[x][i] = static_cast<bool>(pow % 2);
    }
  }
}

LongInt my_sqrt(std::vector<LongInt> &S, LongInt n) {
  LongInt sqrt_n = 1;
  for (auto &prime : S) {
    LongInt pow = make_free_of(prime, n);
    sqrt_n *= poww(prime, pow / 2);
  }
  return sqrt_n;
}
} // namespace bpm
