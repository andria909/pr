#include "fft.h"
#include <algorithm>

namespace bpm {
LongDouble pi = LongDouble{"3."
                           "141592653589793238462643383279502884197169399375105"
                           "8209749445923078164062862089986280348253421170679"};
LongDouble factorial(int n) {
  LongDouble result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

LongDouble my_sin(LongDouble x) {
  LongDouble result = 0;
  LongDouble term = x;
  int n = 1;

  while (abs(term) > 1e-100) {
    result += term;
    n += 2;
    term *= -x * x / (n * (n - 1));
  }

  return result;
}

LongDouble my_cos(LongDouble x) {
  LongDouble result = 0;
  LongDouble term = 1;
  int n = 0;

  while (abs(term) > 1e-100) {
    result += term;
    n += 2;
    term *= -x * x / (n * (n - 1));
  }

  return result;
}

void fft(std::vector<base> &a, bool invert) {
  int n = (int)a.size();
  if (n == 1)
    return;

  std::vector<base> a0(n / 2), a1(n / 2);
  for (int i = 0, j = 0; i < n; i += 2, ++j) {
    a0[j] = a[i];
    a1[j] = a[i + 1];
  }

  fft(a0, invert);
  fft(a1, invert);

  LongDouble ang = 2 * pi / n * (invert ? -1 : 1);
  base w(LongDouble{1}), wn(my_cos(ang), my_sin(ang));

  for (int i = 0; i < n / 2; ++i) {
    a[i] = a0[i] + w * a1[i];
    a[i + n / 2] = a0[i] - w * a1[i];
    if (invert) {
      a[i] /= 2;
      a[i + n / 2] /= 2;
    }
    w *= wn;
  }
}

std::vector<LongInt> multiply(const std::vector<LongInt> &a,
                              const std::vector<LongInt> &b,
                              const LongInt &mod_n) {
  std::vector<base> fa, fb;
  fa.reserve(a.size());
  fb.reserve(b.size());

  for (const auto &val : a) {
    LongInt mod_val = val % mod_n;
    fa.push_back(base(mod_val.convert_to<LongDouble>(), 0));
  }

  for (const auto &val : b) {
    LongInt mod_val = val % mod_n;
    fb.push_back(base(mod_val.convert_to<LongDouble>(), 0));
  }

  size_t n = 1;
  while (n < a.size() + b.size())
    n *= 2;

  fa.resize(n);
  fb.resize(n);

  fft(fa, false);
  fft(fb, false);

  for (size_t i = 0; i < n; ++i)
    fa[i] *= fb[i];

  fft(fa, true);

  std::vector<LongInt> result(n);
  for (size_t i = 0; i < n; ++i)
    result[i] = static_cast<LongInt>(round(fa[i].real())) % mod_n;

  while (result.size() > 1 && result.back() == 0)
    result.pop_back();

  return result;
}

std::vector<LongInt> power_mod(const std::vector<LongInt> &base,
                               LongInt exponent, const LongInt &r,
                               const LongInt &mod_n) {
  size_t r_int = r.convert_to<size_t>();

  std::vector<LongInt> result(r_int, 0);
  result[0] = 1;

  std::vector<LongInt> current = base;

  while (exponent > 0) {
    if (exponent % 2 == 1) {
      std::vector<LongInt> temp = multiply(result, current, mod_n);

      std::vector<LongInt> mod_result(r_int, 0);
      for (size_t i = 0; i < temp.size(); ++i) {
        size_t idx = i % r_int;
        mod_result[idx] = (mod_result[idx] + temp[i]) % mod_n;
      }

      result = mod_result;
    }

    std::vector<LongInt> temp = multiply(current, current, mod_n);

    std::vector<LongInt> mod_current(r_int, 0);
    for (size_t i = 0; i < temp.size(); ++i) {
      size_t idx = i % r_int;
      mod_current[idx] = (mod_current[idx] + temp[i]) % mod_n;
    }

    current = mod_current;
    exponent /= 2;
  }

  return result;
}

bool check_congruence(const LongInt &a, const LongInt &n, const LongInt &r) {
  size_t r_int = r.convert_to<size_t>();

  std::vector<LongInt> polynomial(2);
  polynomial[0] = a;
  polynomial[1] = 1;

  std::vector<LongInt> left_side = power_mod(polynomial, n, r, n);

  std::vector<LongInt> right_side(r_int, 0);
  right_side[0] = a;

  LongInt n_mod_r = n % r;
  size_t n_mod_r_int = n_mod_r.convert_to<size_t>();

  right_side[n_mod_r_int] = (right_side[n_mod_r_int] + 1) % n;

  for (size_t i = 0; i < r_int; ++i) {
    if (left_side[i] != right_side[i])
      return false;
  }

  return true;
}
} // namespace bpm