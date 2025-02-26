#include "utils.h"

cpp_int phi(cpp_int n) {
  cpp_int res = n;
  for (cpp_int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      while (n % i == 0) {
        n /= i;
      }
      res -= res / i;
    }
  }
  if (n > 1) {
    res -= res / n;
  }
  return res;
}

int jacobi(cpp_int q, cpp_int p) {
  cpp_int s = 0, u = q, v = p;
  cpp_int r, k, t;
  do {
    r = u % v;
    k = t = 0;
    while (r % 2 == 0) {
      k++;
      r >>= 1;
    }
    t = r;
    s = (s + k * ((v % 8) * (v % 8) - 1) / 8 + (t - 1) * (v - 1) / 4) % 2;
    if (t == 1)
      return (s) ? -1 : 1;
    u = v;
    v = t;
  } while (t >= 3);
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

cpp_int pow(cpp_int base, cpp_int exp) {
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
    for(cpp_int a = 2; a * a <= n; ++a) {
        cpp_int l = 1;
        cpp_int r = n;
        cpp_int power;
        while (r - l > 1) {
            cpp_int mid = (l + r) / 2;
            power = pow(a, mid);
            if (power == n) {
                return true;
            } 
            else if (power < n) {
                l = mid;
            }
            else {
                r = mid;
            }
        }
        if (pow(a, l) == n || pow(a, r) == n) {
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

    if ((pow(2, result)) < n) {
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
        if (found) return r;
        ++r;
    }
}
